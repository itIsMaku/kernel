#pragma once
#include <stddef.h>

void heap_init(void* start, size_t size);
void* malloc(size_t size);
void free(void* ptr);
void* calloc(size_t n, size_t size);
void* realloc(void* ptr, size_t newsize);

size_t heap_used();
size_t heap_free();
