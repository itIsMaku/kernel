#include "vga.h"
#include "../lib/string.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_MEMORY ((unsigned short *)0xB8000)

static size_t row = 0;
static size_t col = 0;
static unsigned char color = 0x0F;

static inline unsigned short vga_entry(char c, unsigned char color) {
    return (unsigned short)c | (unsigned short)color << 8;
}

static void scroll(void) {
    if (row < VGA_HEIGHT)
        return;

    for (size_t y = 1; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            VGA_MEMORY[(y - 1) * VGA_WIDTH + x] =
                VGA_MEMORY[y * VGA_WIDTH + x];
        }
    }

    for (size_t x = 0; x < VGA_WIDTH; x++) {
        VGA_MEMORY[(VGA_HEIGHT - 1) * VGA_WIDTH + x] =
            vga_entry(' ', color);
    }

    row = VGA_HEIGHT - 1;
}

void vga_clear(void) {
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            VGA_MEMORY[y * VGA_WIDTH + x] =
                vga_entry(' ', color);
        }
    }
    row = 0;
    col = 0;
}

void vga_putc(char c) {
    if (c == '\n') {
        col = 0;
        row++;
        scroll();
        return;
    } else if (c == '\b') {
        if (col > 0) {
            col--;
            VGA_MEMORY[row * VGA_WIDTH + col] = vga_entry(' ', color);
        }
        return;
    }

    VGA_MEMORY[row * VGA_WIDTH + col] = vga_entry(c, color);
    col++;
    if (col >= VGA_WIDTH) {
        col = 0;
        row++;
        scroll();
    }
}

void vga_print(const char* str) {
    for (size_t i = 0; str[i]; i++) {
        vga_putc(str[i]);
    }
}
