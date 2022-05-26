#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/time.h>

#define CBC 1


#include "aes.h"
#include "base64.h"
#include "pkcs7_padding.h"

static const uint8_t *key = "B31F2A75FBF94099";
static const uint8_t *iv = "1234567890123456";
static const unsigned char *base_src = "GyICyfqhJyFFvxpSkYMRaCECDDoteRkdAuEluGxPesfBlWOoYjmhRWJbpNUzXzESSpXXtgbqGEqjGPcPKkXrPeeMbZIBWRXVNHMM";

int intlen(int i) {
    char str[10];
    sprintf(str, "%d", i);
    return strlen(str);
}

int times_run(int times) {
    size_t base_src_len = strlen(base_src);
    int modulus = 16;

    for (int i = 0; i < times; ++i) {
        size_t src_len = base_src_len + intlen(i);

        int src_size = src_len + modulus - (src_len % modulus);
        unsigned char *src = malloc(src_size);
        sprintf(src, "%s%d", base_src, i);
        printf("SRC:%s\n", src);

        pkcs7_padding_pad_buffer(src, src_len, src_size, modulus);

        struct AES_ctx ctx1;
        AES_init_ctx_iv(&ctx1, key, iv);
        AES_CBC_encrypt_buffer(&ctx1, src, src_size);

        char *b = malloc(Base64encode_len(src_size));
        Base64encode(b, src, src_size);
        printf("AES:%s\n", b);

        int decode_len = Base64decode_len(b);
        char *decode = malloc(decode_len);
        int nbytes_decoded = Base64decode(decode, b);
        free(b);

        struct AES_ctx ctx;
        AES_init_ctx_iv(&ctx, key, iv);
        AES_CBC_decrypt_buffer(&ctx, decode, nbytes_decoded);
        size_t data_length = pkcs7_padding_data_length(decode, nbytes_decoded, modulus);
        decode[data_length] = 0;

        sprintf(src, "%s%d", base_src, i);
        if (strcmp(src, decode) != 0) {
            printf("failed!");
            exit(-1);
        }

        free(src);
        free(decode);
    }
}

const int TIMES = 1;

int main() {
    struct timeval start, end;
    gettimeofday(&start, NULL);

    times_run(TIMES);

    gettimeofday(&end, NULL);

    long start_millis = start.tv_sec * 1000 + start.tv_usec / 1000;
    long end_millis = end.tv_sec * 1000 + end.tv_usec / 1000;
    printf("%ld-%ld\n", start_millis, end_millis);
    long millis = end_millis - start_millis;

    printf("cost %ld times/millis\n", TIMES / millis);
}


