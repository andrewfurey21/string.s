.intel_syntax noprefix

.extern main
.global _start
.global print

.section .text
_start:
    xor rax, rax
    call main

    mov rdi, rax
    mov rax, 60
    syscall

print:
    mov rdx, rsi # count
    mov rsi, rdi # buf
    mov rdi, 1   # fd
    mov rax, 1   # write
    syscall
    ret
