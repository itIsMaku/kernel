#pragma once

#include <stddef.h> 

#define CMD_NAME_MAX 16

typedef struct {
    const char name[CMD_NAME_MAX];
    void (*func)(const char* args);
    const char* description;
} command_t;


extern command_t commands[];
extern const size_t COMMAND_COUNT;