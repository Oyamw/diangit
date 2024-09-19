#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <direct.h> // ��Ӵ�����ʹ�� _mkdir

void create_git_repo(const char* git_dir) {
    // ����Ƿ��Ѵ��ڲֿ�
    char path[256];
    snprintf(path, sizeof(path), "%s/.git", git_dir);
    if (_mkdir(git_dir) != 0) { // ʹ�� _mkdir
        printf("�ֿ��Ѵ���: %s\n", path);
        return;
    }

    // ���� .git Ŀ¼
    if (_mkdir(path) != 0) { // ʹ�� _mkdir
        perror("���� .git Ŀ¼ʧ��");
        return;
    }

    // ���� config �ļ�
    snprintf(path, sizeof(path), "%s/.git/config", git_dir);
    FILE* config_file = fopen(path, "w");
    if (config_file) {
        fprintf(config_file, "[core]\n");
        fprintf(config_file, "\trepositoryformatversion = 0\n");
        fprintf(config_file, "\tfilemode = false\n");
        fclose(config_file);
    }
    else {
        perror("���� config �ļ�ʧ��");
    }

    printf("�ɹ���ʼ�� Git �ֿ�: %s\n", git_dir);
}

int main(int argc, char* argv[]) {
    const char* dir = (argc > 1) ? argv[1] : ".";
    create_git_repo(dir);
    return 0;
}
