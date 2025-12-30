#include "stdio.h"
#include "../drivers/vga.h"

static void itoa(int value, char* buffer) {
    char tmp[16];
    int i = 0;
    int neg = 0;

    if (value == 0) {
        buffer[0] = '0';
        buffer[1] = 0;
        return;
    }

    if (value < 0) {
        neg = 1;
        value = -value;
    }

    while (value > 0) {
        tmp[i++] = '0' + (value % 10);
        value /= 10;
    }

    int j = 0;
    if (neg)
        buffer[j++] = '-';

    while (i--) {
        buffer[j++] = tmp[i];
    }

    buffer[j] = 0;
}

void print(const char* str) {
    vga_print(str, 15);
}

void print_colored(const char* str, unsigned char color) {
    vga_print(str, color);
}

void print_int(int value) {
    char buf[16];
    itoa(value, buf);
    vga_print(buf, 15);
}

void print_hex(unsigned int value) {
    char hex[11] = "0x00000000";
    const char* digits = "0123456789ABCDEF";

    for (int i = 9; i >= 2; i--) {
        hex[i] = digits[value & 0xF];
        value >>= 4;
    }

    vga_print(hex, 15);
}

void panic(const char* msg) {
    vga_clear();
    vga_print("KERNEL PANIC:\n", 15);
    vga_print(msg, 15);
    while (1)
        __asm__("cli; hlt");
}
