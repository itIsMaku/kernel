#include "drivers/vga.h"
#include "drivers/keyboard.h"
#include "lib/stdio.h"
#include "shell/shell.h"

void kmain(void) {
    vga_clear();
    print_info();
    shell_run();
}
