.intel_syntax noprefix

.global memset
.global memcpy
.global memmove

.section .text

# void * memset(const void * s, i32 c, u64 n);
memset:
    xor rax, rax
_memset_start:
    cmp rax, rdx
    je _memset_end
    mov BYTE PTR [rdi + rax], sil
    inc rax
    jmp _memset_start
_memset_end:
    mov rax, rdi
    ret

# void * memcpy(void * d, const void * s, u64 n);
memcpy:
    xor rax, rax
    mov rcx, rdi
_memcpy_start:
    cmp rax, rdx
    je _memcpy_end
    movsb
    inc rax
    jmp _memcpy_start
_memcpy_end:
    mov rax, rcx
    ret

# void * memmove(void * d, const void * s, u64 n);
memmove:
    ret

