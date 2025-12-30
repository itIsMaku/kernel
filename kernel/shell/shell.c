#include "shell.h"
#include "commands.h"
#include "../drivers/vga.h"
#include "../drivers/keyboard.h"
#include "../lib/string.h"
#include "../lib/stdio.h"
#include "../lib/memory.h"
#include "shutdown.h"
#include "../lib/string_dyn.h"

#define SHELL_MAX_INPUT 128
#define SHELL_PROMPT "VolkmanOS> "

static void execute_command(char* input) {
    if (strlen(input) == 0) return;

    char* space = strchr(input, ' ');
    char command_name[CMD_NAME_MAX];

    if (space) {
        size_t len = space - input;
        if (len >= CMD_NAME_MAX) len = CMD_NAME_MAX - 1;
        strncpy(command_name, input, len);
        command_name[len] = 0;
    } else {
        strncpy(command_name, input, CMD_NAME_MAX - 1);
        command_name[CMD_NAME_MAX - 1] = 0;
    }

    const char* args = space ? (space + 1) : "";

    for (size_t i = 0; i < COMMAND_COUNT; i++) {
        if (strcmp(command_name, commands[i].name) == 0) {
            commands[i].func(args);
            return;
        }
    }

    print_colored("\nUnknown command: ", 12);
    print_colored(input, 12);
    print("\n");
}

void shell_run(void) {
    while (1) {
        String input = string_new(32);

        print_colored(SHELL_PROMPT, 7);

        while (1) {
            char c = get_char();

            if (c == '\n') { // enter
                vga_putc('\n', 15);
                string_append_char(&input, 0);
                execute_command(input.data);
                break;
            } else if (c == '\b') { // backspace
                if (input.len > 0) {
                    input.len--;
                    vga_putc('\b', 15);
                }
            } else {
                string_append_char(&input, c);
                vga_putc(c, 15);
                // if (pos < SHELL_MAX_INPUT - 1) {
                //     input[pos++] = c;
                //     vga_putc(c, 15);
                // }
            }
        }

        string_free(&input);
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
    print(" - heap memory allocator (malloc/free)\n");

    print_colored("\nTip: Type 'help' to see all available commands.\n", 10);

    print("\nEnjoy exploring my custom kernel. :)\n\n");
}