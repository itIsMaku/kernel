#include "drivers/vga.h"
#include "drivers/keyboard.h"
#include "lib/stdio.h"
#include "shell/shell.h"

void kmain(void) {
    vga_clear();
    print("Welcome to VolkmanOS - kernel basics learning shit\n");
    shell_run();
}
