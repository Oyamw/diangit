#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define SHA256_BLOCK_SIZE 32

// SHA256 算法的简化实现
void sha256(const char* str, uint8_t* output) {
    // 这里可以插入一个简单的 SHA256 实现
    // 本示例中将只做一个占位符
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

