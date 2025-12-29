#include "keyboard.h"
#include "../drivers/vga.h"

#define DATA_PORT 0x60
#define STATUS_PORT 0x64
#define OUTPUT_BUFFER_FULL 0x01

static inline unsigned char inb(unsigned short port) {
    unsigned char ret;
    __asm__ volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

static const char scancode_ascii[128] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0,
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',
    0, '*', 0, ' ', 0 };

char get_char(void) {
    unsigned char scancode;

    while (1)
    {
        if (inb(STATUS_PORT) & OUTPUT_BUFFER_FULL)
        {
            scancode = inb(DATA_PORT);

            if (!(scancode & 0x80) && scancode < 128 && scancode_ascii[scancode] != 0)
            {
                return scancode_ascii[scancode];
            }
        }
    }
}
  