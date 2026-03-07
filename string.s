.intel_syntax noprefix

.global memset

.section .text

# void * memset(const void * s, i32 c, u64 n);
# compare going forward and backwards with gbench
memset:
    xor rax, rax
memset_start:
    cmp rax, rdx
    je memset_end
    mov BYTE PTR [rdi + rax], sil
    inc rax
    jmp memset_start
memset_end:
    ret
