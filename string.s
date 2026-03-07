.intel_syntax noprefix

.global memset
.global memcpy
.global memmove
.global memcmp
.global memchr
.global memccpy

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
# could be smarter and not save what you don't need.
memmove:
    push rbp
    mov rbp, rsp

    sub rsp, rdx # allocate n byte buffer on stack

    mov rcx, rdi # preserve d and buffer
    mov r8, rsp

    mov rdi, rsp # copy s onto buffer
    xor rax, rax
_memmove_save_buf:
    cmp rax, rdx
    je _memmove_end_buf
    movsb
    inc rax
    jmp _memmove_save_buf
_memmove_end_buf:

    mov rdi, rcx # copy buffer onto d
    mov rsi, r8
    xor rax, rax
_memmove_save_d:
    cmp rax, rdx
    je _memmove_end_d
    movsb
    inc rax
    jmp _memmove_save_d
_memmove_end_d:
    mov rax, rcx
    leave
    ret

# i32 memcmp(const void * s1, const void * s2, u64 n);
memcmp:
    xor rcx, rcx
    xor rax, rax
_memcmp_start:
    cmp rcx, rdx
    je _memcmp_end
    cmpsb
    jb _memcmp_greater
    ja _memcmp_less
    inc rcx
    jmp _memcmp_start
_memcmp_greater:
    mov eax, 1
    jmp _memcmp_end
_memcmp_less:
    mov eax, -1
_memcmp_end:
    ret

# void * memchr(const void * s, i32 c, u64 n);
memchr:
    xor rcx, rcx
    xor rax, rax
_memchr_start:
    cmp rcx, rdx
    je _memchr_end
    cmp BYTE PTR [rdi], sil
    je _memchr_found
    inc rdi
    inc rcx
    jmp _memchr_start
_memchr_found:
    mov rax, rdi
_memchr_end:
    ret

# void * memccpy(void * d, const void * s, i32 c, u64 n);
memccpy:
    xor rax, rax
    mov r9, rdi
_memccpy_start:
    cmp rax, rcx
    je _memccpy_end
    inc rax
    mov r8b, BYTE PTR [rsi]
    movsb
    cmp dl, r8b
    je _memccpy_end
    jmp _memccpy_start
_memccpy_end:
    lea rax, [r9 + rax]
    ret
