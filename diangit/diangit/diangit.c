#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <direct.h> // 添加此行以使用 _mkdir

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

int main(int argc, char* argv[]) {
    const char* dir = (argc > 1) ? argv[1] : ".";
    create_git_repo(dir);
    return 0;
}
