#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h> // 添加此行以使用 _mkdir
#include <stdint.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>// 可选，处理错误
#include <direct.h> // 对于 _mkdir

#define SHA_HASH_LEN 40  // 假设哈希长度为40
#define SHA256_BLOCK_SIZE 32// SHA256 算法的简化实现

typedef struct {
    char message[256]; // 提交信息
    time_t timestamp;  // 提交时间戳
} Commit;

void create_git_repo(const char* git_dir) {
    // 检查是否已存在仓库
    char path[256];
    snprintf(path, sizeof(path), "%s/.git", git_dir);
    if (_mkdir(git_dir) != 0) { // 使用 _mkdir
        printf("仓库已存在: %s\n", path);
        return;
    }

    // 创建 .git 目录
    if (_mkdir(path) != 0) { // 使用 _mkdir
        perror("创建 .git 目录失败");
        return;
    }

    // 创建 config 文件
    snprintf(path, sizeof(path), "%s/.git/config", git_dir);
    FILE* config_file = fopen(path, "w");
    if (config_file) {
        fprintf(config_file, "[core]\n");
        fprintf(config_file, "\trepositoryformatversion = 0\n");
        fprintf(config_file, "\tfilemode = false\n");
        fclose(config_file);
    }
    else {
        perror("创建 config 文件失败");
    }

    printf("成功初始化 Git 仓库: %s\n", git_dir);
}

void sha256(const char* str, uint8_t* output) {
    // 这里可以插入一个简单的 SHA256 实现
    // 本示例中将只做一个占位符
    memset(output, 0, SHA256_BLOCK_SIZE);
    snprintf((char*)output, SHA256_BLOCK_SIZE, "hash_of_%s", str);
}

void save_commit(Commit* commit) {
    char path[256];
    snprintf(path, sizeof(path), ".git/objects/%ld", commit->timestamp);
    FILE* commit_file = fopen(path, "wb");
    if (commit_file) {
        fwrite(commit, sizeof(Commit), 1, commit_file);
        fclose(commit_file);
    }
    else {
        perror("无法保存提交对象");
    }
}

void commit(char* message) {
    Commit new_commit;
    new_commit.timestamp = time(NULL);
    strncpy(new_commit.message, message, sizeof(new_commit.message) - 1);
    new_commit.message[sizeof(new_commit.message) - 1] = '\0';

    save_commit(&new_commit);
}

void log_commits() {
    printf("提交日志:\n");
    for (long i = time(NULL); i >= 0; i--) {
        char path[256];
        snprintf(path, sizeof(path), ".git/objects/%ld", i);
        FILE* commit_file = fopen(path, "rb");
        if (commit_file) {
            Commit commit;
            fread(&commit, sizeof(Commit), 1, commit_file);
            fclose(commit_file);
            printf("时间: %s信息: %s\n", ctime(&commit.timestamp), commit.message);
        }
    }
}

void checkout(const char* commit) {
    char command[256];
    snprintf(command, sizeof(command), "git checkout %s", commit);
    system(command);
    printf("已切换到提交: %s\n", commit);
}

void ls_tree(const char* commit) {
    char command[256];
    snprintf(command, sizeof(command), "git ls-tree --name-only %s", commit);
    system(command);
}

void get_current_commit_hash(char* hash_buffer) {
    FILE* head_file = fopen("HEAD", "r");
    if (head_file) {
        char ref[256];
        fgets(ref, sizeof(ref), head_file);
        // 提取分支名称
        char branch[256];
        sscanf(ref, "ref: refs/heads/%s", branch);

        // 读取分支文件中的哈希值
        char branch_path[256];
        snprintf(branch_path, sizeof(branch_path), "refs/heads/%s", branch);
        FILE* branch_file = fopen(branch_path, "r");
        if (branch_file) {
            fgets(hash_buffer, SHA_HASH_LEN + 1, branch_file);
            fclose(branch_file);
        }
        fclose(head_file);
    }
    else {
        perror("Error reading HEAD");
    }
}

void create_branch(const char* branch_name) {
    char current_commit_hash[SHA_HASH_LEN];
    get_current_commit_hash(current_commit_hash);

    char branch_path[256];
    snprintf(branch_path, sizeof(branch_path), "refs/heads/%s", branch_name);

    FILE* branch_file = fopen(branch_path, "w");
    if (branch_file) {
        fprintf(branch_file, "%s", current_commit_hash);
        fclose(branch_file);
        printf("Branch '%s' created successfully.\n", branch_name);
    }
    else {
        perror("Error creating branch");
    }
}

void create_tag(const char* tag_name) {
    char current_commit_hash[SHA_HASH_LEN];
    get_current_commit_hash(current_commit_hash);

    char tag_path[256];
    snprintf(tag_path, sizeof(tag_path), "refs/tags/%s", tag_name);

    FILE* tag_file = fopen(tag_path, "w");
    if (tag_file) {
        fprintf(tag_file, "%s", current_commit_hash);
        fclose(tag_file);
        printf("Tag '%s' created successfully.\n", tag_name);
    }
    else {
        perror("Error creating tag");
    }
}

void list_branches() {
    DIR* dir;
    struct dirent* entry;

    dir = opendir(".git/refs/heads");
    if (dir == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.') continue; // Skip hidden files
        printf("Branch: %s\n", entry->d_name);
    }

    closedir(dir);
}

void list_tags() {
    DIR* dir;
    struct dirent* entry;

    dir = opendir(".git/refs/tags");
    if (dir == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.') continue; // Skip hidden files
        printf("Tag: %s\n", entry->d_name);
    }

    closedir(dir);
}

void display_menu() {
    printf("Git CLI\n");
    printf("1. Create Branch\n");
    printf("2. Create Tag\n");
    printf("3. List Branches\n");
    printf("4. List Tags\n");
    printf("5. Exit\n");
}

void add_file(const char* filename) {
    // 打开文件以计算哈希值（这里我们使用文件名作为示例）
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("无法打开文件: %s\n", filename);
        return;
    }

    // 计算文件的哈希值（简单示例，实际使用时需要用哈希函数）
    char hash[41]; // 假设使用 SHA-1, 长度为 40 + 1 结束符
    snprintf(hash, sizeof(hash), "hash_of_%s", filename); // 示例哈希

    // 将文件哈希值添加到暂存区
    FILE* index = fopen(".diangit/index", "a");
    fprintf(index, "%s %s\n", hash, filename);
    fclose(index);
    fclose(file);

    printf("已添加文件: %s\n", filename);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "用法: %s <命令> [参数]\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "init") == 0) {
        const char* dir = (argc > 2) ? argv[2] : ".";
        create_git_repo(dir);
    }
    else if (strcmp(argv[1], "hash") == 0) {
        if (argc < 3) {
            fprintf(stderr, "用法: %s hash <string_to_hash>\n", argv[0]);
            return 1;
        }
        uint8_t hash[SHA256_BLOCK_SIZE];
        sha256(argv[2], hash);
        printf("Hash: ");
        for (int i = 0; i < SHA256_BLOCK_SIZE; i++) {
            printf("%02x", hash[i]);
        }
        printf("\n");
    }
    else if (strcmp(argv[1], "commit") == 0 && argc >= 3) {
        commit(argv[2]);
        printf("提交成功: %s\n", argv[2]);
    }
    else if (strcmp(argv[1], "log") == 0) {
        log_commits();
    }
    else if (strcmp(argv[1], "checkout") == 0 && argc >= 3) {
        checkout(argv[2]);
    }
    else if (strcmp(argv[1], "ls-tree") == 0 && argc >= 3) {
        ls_tree(argv[2]);
    }
    else if (strcmp(argv[1], "add") == 0 && argc >= 3) {
        add_file(argv[2]);
    }
    else if (strcmp(argv[1], "branch") == 0 && argc >= 3) {
        create_branch(argv[2]);
    }
    else if (strcmp(argv[1], "tag") == 0 && argc >= 3) {
        create_tag(argv[2]);
    }
    else if (strcmp(argv[1], "list-branches") == 0) {
        list_branches();
    }
    else if (strcmp(argv[1], "list-tags") == 0) {
        list_tags();
    }
    else if (strcmp(argv[1], "menu") == 0) {
        int choice;
        char name[256];
        while (1) {
            display_menu();
            printf("Enter your choice: ");
            scanf("%d", &choice);
            switch (choice) {
            case 1:
                printf("Enter branch name: ");
                scanf("%s", name);
                create_branch(name);
                break;
            case 2:
                printf("Enter tag name: ");
                scanf("%s", name);
                create_tag(name);
                break;
            case 3:
                list_branches();
                break;
            case 4:
                list_tags();
                break;
            case 5:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
            }
        }
    }
    else {
        fprintf(stderr, "未知命令: %s\n", argv[1]);
        return 1;
    }

    return 0;
}