#pragma once

#include <stddef.h>

size_t strlen(const char* str);
int strcmp(const char* a, const char* b);
int strncmp(const char* a, const char* b, size_t n);
void strncpy(char* dest, const char* src, size_t n);
char* strchr(const char* s, int c);