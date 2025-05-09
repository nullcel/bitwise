#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "encrypt.h"

#define MODE_ENCRYPT 1
#define MODE_DECRYPT 2

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <encrypt|decrypt> <text>\n", argv[0]);
        return 1;
    }

    int mode = 0;
    if (strcmp(argv[1], "encrypt") == 0) mode = MODE_ENCRYPT;
    else if (strcmp(argv[1], "decrypt") == 0) mode = MODE_DECRYPT;
    else {
        printf("Invalid mode. Use 'encrypt' or 'decrypt'.\n");
        return 1;
    }

    const char *input = argv[2];
    char output[33] = {0};

    if (mode == MODE_ENCRYPT) {
        encrypt(input, output);
        printf("Encrypted: %s\n", output);
    } else {
        char decrypted[1024];
        decrypt(input, decrypted);
        printf("Decrypted: %s\n", decrypted);
    }

    return 0;
} 
