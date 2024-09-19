#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void add_file(const char* filename) {
    // ���ļ��Լ����ϣֵ����������ʹ���ļ�����Ϊʾ����
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("�޷����ļ�: %s\n", filename);
        return;
    }

    // �����ļ��Ĺ�ϣֵ����ʾ����ʵ��ʹ��ʱ��Ҫ�ù�ϣ������
    char hash[41]; // ����ʹ�� SHA-1, ����Ϊ 40 + 1 ������
    snprintf(hash, sizeof(hash), "hash_of_%s", filename); // ʾ����ϣ

    // ���ļ���ϣֵ��ӵ��ݴ���
    FILE* index = fopen(".diangit/index", "a");
    fprintf(index, "%s %s\n", hash, filename);
    fclose(index);
    fclose(file);

    printf("������ļ�: %s\n", filename);
}

int main(int argc, char* argv[]) {
    if (argc != 3 || strcmp(argv[1], "add") != 0) {
        printf("�÷�: diangit add <filename>\n");
        return 1;
    }
    add_file(argv[2]);
    return 0;
}
