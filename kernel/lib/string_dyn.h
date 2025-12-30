#pragma once
#include <stddef.h>
#include <stdint.h>

typedef struct {
    char* data;
    size_t len;
    size_t cap;
} String;

String string_new(size_t cap);
void string_free(String* s);
void string_clear(String* s);

void string_append_char(String* s, char c);
void string_append_cstr(String* s, const char* cstr);
void string_append_string(String* s, const String* other);

size_t string_length(const String* s);
char string_get(const String* s, size_t index);
void string_set(String* s, size_t index, char c);
int string_contains(const String* s, char c);
int string_index_of(const String* s, char c);

String string_substring(const String* s, size_t start, size_t end);
String* string_split(const String* s, char sep, size_t* out_count);

void string_print(const String* s);
