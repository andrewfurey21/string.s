.intel_syntax noprefix

.extern main
.global _start

.section .text
_start:
    xor rax, rax
    call main

    mov rdi, rax
    mov rax, 60
    syscall
