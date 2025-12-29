#include "string.h"

size_t strlen(const char* str) {
    size_t len = 0;
    while (str[len])
    {
        len++;
    }
    return len;
}

int strcmp(const char* a, const char* b) {
    while (*a && (*a == *b))
    {
        a++;
        b++;
    }
    return *(unsigned char*)a - *(unsigned char*)b;
}

int strncmp(const char* a, const char* b, size_t n) {
    while (n && *a && (*a == *b))
    {
        a++;
        b++;
        n--;
    }

    if (n == 0)
        return 0;
    return *(unsigned char*)a - *(unsigned char*)b;
}

char* strcpy(char* dest, const char* src) {
    char* ret = dest;
    while ((*dest++ = *src++))
        ;
    return ret;
}
