.intel_syntax noprefix

.global println
.global exit

.section .rodata
newline:
    .asciz "\n"

.section .text
print:
    mov rdx, rsi # count
    mov rsi, rdi # buf
    mov rdi, 1   # fd
    mov rax, 1   # write
    syscall
    ret

println:
    call print
    lea rdi, [rip + newline]
    mov rsi, 1
    call print
    ret

exit:
    mov rax, 60
    syscall
