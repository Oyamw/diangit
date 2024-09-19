#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char message[256]; // �ύ��Ϣ
    time_t timestamp;  // �ύʱ���
} Commit;

void save_commit(Commit* commit) {
    char path[256];
    snprintf(path, sizeof(path), ".git/objects/%ld", commit->timestamp);
    FILE* commit_file = fopen(path, "wb");
    if (commit_file) {
        fwrite(commit, sizeof(Commit), 1, commit_file);
        fclose(commit_file);
    }
    else {
        perror("�޷������ύ����");
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
    printf("�ύ��־:\n");
    for (long i = time(NULL); i >= 0; i--) {
        char path[256];
        snprintf(path, sizeof(path), ".git/objects/%ld", i);
        FILE* commit_file = fopen(path, "rb");
        if (commit_file) {
            Commit commit;
            fread(&commit, sizeof(Commit), 1, commit_file);
            fclose(commit_file);
            printf("ʱ��: %s��Ϣ: %s\n", ctime(&commit.timestamp), commit.message);
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "�÷�: %s <����> [����]\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "commit") == 0 && argc >= 3) {
        commit(argv[2]);
        printf("�ύ�ɹ�: %s\n", argv[2]);
    }
    else if (strcmp(argv[1], "log") == 0) {
        log_commits();
    }
    else {
        fprintf(stderr, "δ֪����: %s\n", argv[1]);
    }

    return 0;
}
