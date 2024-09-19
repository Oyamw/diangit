#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    if (argc != 3 || strcmp(argv[1], "add") != 0) {
        printf("用法: diangit add <filename>\n");
        return 1;
    }
    add_file(argv[2]);
    return 0;
}
