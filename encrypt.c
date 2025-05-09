#include "encrypt.h"
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define ROUNDS 50000000
#define STATE_SIZE 16

// Map 4-bit value to a-z0-9
char base36_map[36] = "abcdefghijklmnopqrstuvwxyz0123456789";

static uint8_t sbox(uint8_t val) {
    return (val * 19 + 37) ^ (val >> 1);
}

void transform(uint8_t *state, const char *input) {
    size_t len = strlen(input);
    for (int i = 0; i < ROUNDS; i++) {
        for (int j = 0; j < STATE_SIZE; j++) {
            uint8_t in_byte = input[(i + j) % len];
            state[j] ^= sbox(in_byte ^ state[(j + 3) % STATE_SIZE]);
            state[j] = (state[j] << 1) | (state[j] >> 7); // Rotate left
        }
    }
}

void encode_base36(const uint8_t *state, char *output) {
    for (int i = 0; i < STATE_SIZE; i++) {
        output[2*i] = base36_map[(state[i] >> 4) & 0x0F];
        output[2*i+1] = base36_map[state[i] & 0x0F];
    }
    output[32] = '\0';
}

int reverse_base36(char c) {
    if (c >= 'a' && c <= 'z') return c - 'a';
    if (c >= '0' && c <= '9') return c - '0' + 26;
    return 0;
}

void decode_base36(const char *input, uint8_t *state) {
    for (int i = 0; i < 32; i += 2) {
        int high = reverse_base36(input[i]);
        int low = reverse_base36(input[i+1]);
        state[i/2] = ((high & 0x0F) << 4) | (low & 0x0F);
    }
}

void encrypt(const char *input, char *output) {
    uint8_t state[STATE_SIZE] = {0};
    transform(state, input);
    encode_base36(state, output);
}

void decrypt(const char *input, char *output) {
    // This is a one-way encryption for now
    strcpy(output, "Decryption not implemented (one-way)");
}