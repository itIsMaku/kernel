#include "shell.h"
#include "../drivers/vga.h"
#include "../drivers/keyboard.h"
#include "../lib/string.h"
#include "../lib/stdio.h"
#include "../lib/memory.h"
#include "shutdown.h"

#define SHELL_MAX_INPUT 128

static void execute_command(char* input) {
    if (strcmp(input, "help") == 0)
    {
        print("\nCommands: help, clear, echo <text>, shutdown\n");
    }
    else if (strcmp(input, "clear") == 0)
    {
        vga_clear();
    }
    else if (strncmp(input, "echo ", 5) == 0)
    {
        print(input + 5);
        print("\n");
    }
    else if (strcmp(input, "shutdown") == 0)
    {
        shutdown_system();
    }
    else if (strlen(input) > 0)
    {
        print("\nUnknown command: ");
        print(input);
        print("\n");
    }
}

void shell_run(void) {
    char input[SHELL_MAX_INPUT];
    size_t pos = 0;

    while (1)
    {
        print("VolkmanOS> ");
        pos = 0;
        memset(input, 0, SHELL_MAX_INPUT);

        while (1)
        {
            char c = get_char();

            if (c == '\n')
            { // enter
                vga_putc('\n');
                input[pos] = 0;
                execute_command(input);
                break;
            }
            else if (c == '\b')
            { // backspace
                if (pos > 0)
                    pos--;

                vga_putc('\b');
            }
            else
            {
                if (pos < SHELL_MAX_INPUT - 1)
                {
                    input[pos++] = c;
                    vga_putc(c);
                }
            }
        }
    }
}
