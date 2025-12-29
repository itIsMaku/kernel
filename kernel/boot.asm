section .multiboot
align 4

dd 0x1BADB002          ; multiboot magic
dd 0x00                ; flags
dd -(0x1BADB002)       ; checksum

section .text
global _start
extern kmain

_start:
    cli
    call kmain
.hang:
    hlt
    jmp .hang
