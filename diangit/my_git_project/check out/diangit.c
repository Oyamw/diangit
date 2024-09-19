#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("用法: diangit <命令> [参数]\n");
        return 1;
    }

    if (strcmp(argv[1], "checkout") == 0) {
        if (argc < 3) {
            printf("用法: diangit checkout <提交哈希>\n");
            return 1;
        }
        checkout(argv[2]);
    }
    else if (strcmp(argv[1], "ls-tree") == 0) {
        if (argc < 3) {
            printf("用法: diangit ls-tree <提交哈希>\n");
            return 1;
        }
        ls_tree(argv[2]);
    }
    else {
        printf("未知命令: %s\n", argv[1]);
        return 1;
    }

    return 0;
}

