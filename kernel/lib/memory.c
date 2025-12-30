#include "memory.h"
#include <stdint.h>

typedef struct block {
    size_t size;
    struct block* next;
    int free;
} block_t;

static block_t* free_list = 0;
static uint8_t* heap_start;
static uint8_t* heap_end;

void heap_init(void* start, size_t size) {
    heap_start = (uint8_t*)start;
    heap_end = heap_start + size;

    free_list = (block_t*)heap_start;
    free_list->size = size - sizeof(block_t);
    free_list->next = 0;
    free_list->free = 1;
}

static block_t* find_fit(size_t size) {
    block_t* curr = free_list;
    while (curr) {
        if (curr->free && curr->size >= size) return curr;

        curr = curr->next;
    }

    return 0;
}

void* malloc(size_t size) {
    size = (size + 7) & ~7;

    block_t* block = find_fit(size);
    if (!block) return 0;

    if (block->size >= size + sizeof(block_t) + 8) {
        block_t* new_block = (block_t*)((uint8_t*)block + sizeof(block_t) + size);
        new_block->size = block->size - size - sizeof(block_t);
        new_block->next = block->next;
        new_block->free = 1;

        block->size = size;
        block->next = new_block;
    }

    block->free = 0;

    return (uint8_t*)block + sizeof(block_t);
}

void free(void* ptr) {
    if (!ptr) return;

    block_t* block = (block_t*)((uint8_t*)ptr - sizeof(block_t));
    block->free = 1;

    block_t* curr = free_list;
    while (curr) {
        if (curr->free && curr->next && curr->next->free) {
            curr->size += sizeof(block_t) + curr->next->size;
            curr->next = curr->next->next;
        } else {
            curr = curr->next;
        }
    }
}

void* calloc(size_t n, size_t size) {
    void* ptr = malloc(n * size);
    if (!ptr) return 0;

    uint8_t* p = (uint8_t*)ptr;
    for (size_t i = 0; i < n * size; i++) p[i] = 0;

    return ptr;
}

void* realloc(void* ptr, size_t newsize) {
    if (!ptr) return malloc(newsize);

    block_t* block = (block_t*)((uint8_t*)ptr - sizeof(block_t));
    if (block->size >= newsize) return ptr;

    void* newptr = malloc(newsize);
    if (!newptr) return 0;

    uint8_t* src = (uint8_t*)ptr;
    uint8_t* dst = (uint8_t*)newptr;
    for (size_t i = 0; i < block->size; i++) dst[i] = src[i];

    free(ptr);

    return newptr;
}

size_t heap_used() {
    size_t used = 0;
    block_t* curr = (block_t*)heap_start;
    while ((uint8_t*)curr < heap_end) {
        if (!curr->free) used += curr->size;

        if (!curr->next) break;

        curr = curr->next;
    }

    return used;
}

size_t heap_free() {
    return (heap_end - heap_start) - heap_used();
}
 