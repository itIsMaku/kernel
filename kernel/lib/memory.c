#include "memory.h"

void* memcpy(void* dest, const void* src, size_t n) {
    unsigned char* d = dest;
    const unsigned char* s = src;

    for (size_t i = 0; i < n; i++) {
        d[i] = s[i];
    }
    return dest;
}

void* memset(void* ptr, int value, size_t n) {
    unsigned char* p = ptr;
    unsigned char v = (unsigned char)value;

    for (size_t i = 0; i < n; i++) {
        p[i] = v;
    }
    return ptr;
}

int memcmp(const void* a, const void* b, size_t n) {
    const unsigned char* x = a;
    const unsigned char* y = b;

    for (size_t i = 0; i < n; i++) {
        if (x[i] != y[i]) {
            return x[i] - y[i];
        }
    }
    return 0;
}
