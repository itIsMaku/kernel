#pragma once

#include <stddef.h>

void* memcpy(void* dest, const void* src, size_t n);
void* memset(void* ptr, int value, size_t n);
int memcmp(const void* a, const void* b, size_t n);
