#include "commands.h"
#include "../drivers/vga.h"
#include "../lib/string.h"
#include "../lib/stdio.h"
#include "shutdown.h"
#include "shell.h"

static void cmd_help(const char* args);
static void cmd_clear(const char* args);
static void cmd_echo(const char* args);
static void cmd_shutdown(const char* args);
static void cmd_info(const char* args);
static void cmd_colors(const char* args);

command_t commands[] = {
    {"help", cmd_help, "Display this help message"},
    {"clear", cmd_clear, "Clear the screen"},
    {"echo", cmd_echo, "Echo the input text"},
    {"shutdown", cmd_shutdown, "Shut down the system"},
    {"info", cmd_info, "Display system information"},
    {"colors", cmd_colors, "Display color test"}
};

const size_t COMMAND_COUNT = sizeof(commands) / sizeof(command_t);

static void cmd_help(const char* args) {
    print("\nAvailable commands:\n");
    for (size_t i = 0; i < COMMAND_COUNT; i++) {
        print(" - ");
        print(commands[i].name);
        print(": ");
        print_colored(commands[i].description, 14);
        print("\n");
    }
}

static void cmd_clear(const char* args) {
    vga_clear();
}

static void cmd_echo(const char* args) {
    print(args);
    print("\n");
}

static void cmd_shutdown(const char* args) {
    shutdown_system();
}

static void cmd_info(const char* args) {
    print_info();
}

static void cmd_colors(const char* args) {
    print_colored("\nColor Test:\n", 15);
    for (unsigned char color = 0; color < 16; color++) {
        print("- ");
        print_int(color);
        print(": ");
        print_colored("Sample Text\n", color);
    }
}