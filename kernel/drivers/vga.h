#pragma once
#include <stddef.h>

void vga_clear(void);
void vga_putc(char c, unsigned char color);
void vga_print(const char* str, unsigned char color);
void vga_print_hex(unsigned int value);
void vga_print_dec(int value);
