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

