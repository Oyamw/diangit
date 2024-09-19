#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#define SHA_HASH_LEN 40  // 假设哈希长度为40

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
    if (!dir) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.') continue; // Skip hidden files

        char path[512];
        snprintf(path, sizeof(path), ".git/refs/heads/%s", entry->d_name);
        struct stat file_stat;
        if (stat(path, &file_stat) == 0 && S_ISREG(file_stat.st_mode)) {
            printf("Branch: %s\n", entry->d_name);
        }
    }

    closedir(dir);
}

void list_tags() {
    DIR* dir;
    struct dirent* entry;

    dir = opendir(".git/refs/tags");
    if (!dir) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.') continue; // Skip hidden files

        char path[512];
        snprintf(path, sizeof(path), ".git/refs/tags/%s", entry->d_name);
        struct stat file_stat;
        if (stat(path, &file_stat) == 0 && S_ISREG(file_stat.st_mode)) {
            printf("Tag: %s\n", entry->d_name);
        }
    }

    closedir(dir);
}
