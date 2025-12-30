#include "shell.h"
#include "../drivers/vga.h"
#include "../drivers/keyboard.h"
#include "../lib/string.h"
#include "../lib/stdio.h"
#include "../lib/memory.h"
#include "shutdown.h"

#define SHELL_MAX_INPUT 128
#define SHELL_PROMPT "VolkmanOS> "

static void execute_command(char* input) {
    if (strcmp(input, "help") == 0) {
        print("\nCommands: help, clear, echo <text>, shutdown, info\n");
    } else if (strcmp(input, "clear") == 0) {
        vga_clear();
    } else if (strncmp(input, "echo ", 5) == 0) {
        print(input + 5);
        print("\n");
    } else if (strcmp(input, "shutdown") == 0) {
        shutdown_system();
    } else if (strcmp(input, "info") == 0) {
        print_info();
    } else if (strlen(input) > 0) {
        print_colored("\nUnknown command: ", 12);
        print_colored(input, 12);
        print("\n");
    }
}

void shell_run(void) {
    char input[SHELL_MAX_INPUT];
    size_t pos = 0;

    while (1) {
        pos = 0;
        memset(input, 0, SHELL_MAX_INPUT);

        print_colored(SHELL_PROMPT, 7);

        while (1) {
            char c = get_char();

            if (c == '\n') { // enter
                vga_putc('\n', 15);
                input[pos] = 0;
                execute_command(input);
                break;
            } else if (c == '\b') { // backspace
                if (pos > 0) {
                    pos--;

                    vga_putc('\b', 15);
                }
            } else {
                if (pos < SHELL_MAX_INPUT - 1) {
                    input[pos++] = c;
                    vga_putc(c, 15);
                }
            }
        }
    }
}

void print_info(void) {
    print_colored("__      __   _ _                           ____   _____\n", 10);
    print_colored("\\ \\    / /  | | |                         / __ \\ / ____|\n", 10);
    print_colored(" \\ \\  / /__ | | | ___ __ ___   __ _ _ __ | |  | | (___  \n", 10);
    print_colored("  \\ \\/ / _ \\| | |/ / '_ ` _ \\ / _` | '_ \\| |  | |\\___ \\ \n", 10);
    print_colored("   \\  / (_) | |   <| | | | | | (_| | | | | |__| |____) |\n", 10);
    print_colored("    \\/ \\___/|_|_|\\_\\_| |_| |_|\\__,_|_| |_|\\____/|_____/ \n", 10);

    print("\n\nWelcome to VolkmanOS!\n");

    print("This is a simple educational kernel written from scratch.\n");
    print(" - VGA text output with colored printing\n");
    print(" - basic keyboard input handling with polling\n");
    print(" - simple shell with a few commands\n\n");

    print_colored("\nTip: Type 'help' to see all available commands.\n", 10);

    print("\nEnjoy exploring my custom kernel. :)\n\n");
}