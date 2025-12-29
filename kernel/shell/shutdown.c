#include "shutdown.h"
#include "../lib/stdio.h"

#define PM1a_CNT 0x604

void shutdown_system(void) {
    print("\nShutting down...\n");

    __asm__ volatile(
        "mov $0x2000, %ax\n\t"
        "out %ax, %dx\n\t"
        );

    while (1) __asm__("hlt");
}
