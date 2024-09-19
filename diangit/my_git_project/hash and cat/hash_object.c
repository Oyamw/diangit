#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define SHA256_BLOCK_SIZE 32

// SHA256 �㷨�ļ�ʵ��
void sha256(const char* str, uint8_t* output) {
    // ������Բ���һ���򵥵� SHA256 ʵ��
    // ��ʾ���н�ֻ��һ��ռλ��
    memset(output, 0, SHA256_BLOCK_SIZE);
    snprintf((char*)output, SHA256_BLOCK_SIZE, "hash_of_%s", str);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <string_to_hash>\n", argv[0]);
        return 1;
    }

    uint8_t hash[SHA256_BLOCK_SIZE];
    sha256(argv[1], hash);

    printf("Hash: ");
    for (int i = 0; i < SHA256_BLOCK_SIZE; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");

    return 0;
}

