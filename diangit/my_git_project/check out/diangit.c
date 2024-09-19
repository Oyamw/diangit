#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void checkout(const char* commit) {
    char command[256];
    snprintf(command, sizeof(command), "git checkout %s", commit);
    system(command);
    printf("���л����ύ: %s\n", commit);
}

void ls_tree(const char* commit) {
    char command[256];
    snprintf(command, sizeof(command), "git ls-tree --name-only %s", commit);
    system(command);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("�÷�: diangit <����> [����]\n");
        return 1;
    }

    if (strcmp(argv[1], "checkout") == 0) {
        if (argc < 3) {
            printf("�÷�: diangit checkout <�ύ��ϣ>\n");
            return 1;
        }
        checkout(argv[2]);
    }
    else if (strcmp(argv[1], "ls-tree") == 0) {
        if (argc < 3) {
            printf("�÷�: diangit ls-tree <�ύ��ϣ>\n");
            return 1;
        }
        ls_tree(argv[2]);
    }
    else {
        printf("δ֪����: %s\n", argv[1]);
        return 1;
    }

    return 0;
}

