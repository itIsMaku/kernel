#include "string_dyn.h"
#include "memory.h"
#include "../drivers/vga.h"

#include <stddef.h> 

String string_new(size_t cap) {
    String s;
    s.data = malloc(cap);
    s.len = 0;
    s.cap = cap;
    if (s.data) s.data[0] = 0;

    return s;
}

void string_free(String* s) {
    if (s->data) free(s->data);

    s->data = 0;
    s->len = 0;
    s->cap = 0;
}

void string_clear(String* s) {
    s->len = 0;
    if (s->data) s->data[0] = 0;
}


static void string_ensure_capacity(String* s, size_t extra) {
    if (s->len + extra + 1 > s->cap) { // +1 pro '\0'
        size_t newcap = (s->cap * 2 > s->len + extra + 1) ? s->cap * 2 : s->len + extra + 1;
        char* newdata = malloc(newcap); // free list heap
        for (size_t i = 0; i < s->len; i++) newdata[i] = s->data[i];

        free(s->data);
        s->data = newdata;
        s->cap = newcap;
    }
}

void string_append_char(String* s, char c) {
    string_ensure_capacity(s, 1);
    s->data[s->len++] = c;
    s->data[s->len] = 0;
}

void string_append_cstr(String* s, const char* cstr) {
    for (size_t i = 0; cstr[i]; i++) string_append_char(s, cstr[i]);
}

void string_append_string(String* s, const String* other) {
    for (size_t i = 0; i < other->len; i++) string_append_char(s, other->data[i]);
}


size_t string_length(const String* s) {
    return s->len;
}

char string_get(const String* s, size_t index) {
    if (index >= s->len) return 0;

    return s->data[index];
}

void string_set(String* s, size_t index, char c) {
    if (index < s->len) s->data[index] = c;
}

int string_contains(const String* s, char c) {
    for (size_t i = 0; i < s->len; i++) if (s->data[i] == c) return 1;

    return 0;
}

int string_index_of(const String* s, char c) {
    for (size_t i = 0; i < s->len; i++) if (s->data[i] == c) return i;

    return -1;
}


String string_substring(const String* s, size_t start, size_t end) {
    if (start >= s->len) start = s->len;

    if (end > s->len) end = s->len;

    if (end < start) end = start;

    String sub = string_new(end - start + 1);
    for (size_t i = start; i < end; i++) string_append_char(&sub, s->data[i]);

    return sub;
}

String* string_split(const String* s, char sep, size_t* out_count) {
    size_t count = 1;
    for (size_t i = 0; i < s->len; i++) if (s->data[i] == sep) count++;

    String* parts = malloc(sizeof(String) * count);
    size_t part_idx = 0;
    parts[part_idx] = string_new(16);

    for (size_t i = 0; i < s->len; i++) {
        if (s->data[i] == sep) {
            part_idx++;
            parts[part_idx] = string_new(16);
        } else {
            string_append_char(&parts[part_idx], s->data[i]);
        }
    }

    *out_count = count;

    return parts;
}


void string_print(const String* s) {
    for (size_t i = 0; i < s->len; i++) vga_putc(s->data[i], 15);
}
