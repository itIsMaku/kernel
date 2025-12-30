#include "string.h"

size_t strlen(const char* str) {
    size_t len = 0;
    while (str[len]) {
        len++;
    }
    return len;
}

int strcmp(const char* a, const char* b) {
    while (*a && (*a == *b)) {
        a++;
        b++;
    }
    return *(unsigned char*)a - *(unsigned char*)b;
}

int strncmp(const char* a, const char* b, size_t n) {
    while (n && *a && (*a == *b)) {
        a++;
        b++;
        n--;
    }

    if (n == 0)
        return 0;
    return *(unsigned char*)a - *(unsigned char*)b;
}

char* strchr(const char* s, int c) {
    while (*s) {
        if (*s == (char)c) return (char*)s;

        s++;
    }
    return 0;
}

void strncpy(char* dest, const char* src, size_t n) {
    for (size_t i = 0; i < n; i++) {
        if (src[i] == 0) {
            dest[i] = 0;
            return;
        }
        dest[i] = src[i];
    }
}