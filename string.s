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
    push rdi
    push rsi
    push rdx
    and rdx, 0xffffffffffffffe0

    call memset32

    mov rdi, rax
    mov rsi, QWORD PTR [rsp+8]
    mov rdx, QWORD PTR [rsp]
    and rdx, 0x10

    call memset16

    pop rdx
    and rdx, 0x0f
    pop rsi
    mov rdi, rax

    call memset1

    pop rax
    ret

# args same as memset. returns end
memset32:
    push rsi
    vpbroadcastb ymm0, [rsp]
.Lmemset32.loop:
    test rdx, rdx
    jz .Lmemset32.end
    vmovdqu YMMWORD PTR [rdi], ymm0
    sub rdx, 32
    add rdi, 32
    jmp .Lmemset32.loop
.Lmemset32.end:
    mov rax, rdi
    pop rsi
    ret

memset16:
    push rsi
    vpbroadcastb xmm0, [rsp]
.Lmemset16.loop:
    test rdx, rdx
    je .Lmemset16.end
    vmovdqu XMMWORD PTR [rdi], xmm0
    sub rdx, 16
    add rdi, 16
    jmp .Lmemset16.loop
.Lmemset16.end:
    lea rax, [rdi]
    pop rsi
    ret

memset1:
.Lmemset1.loop:
    test rdx, rdx
    je .Lmemset1.end
    mov BYTE PTR [rdi], sil
    inc rdi
    dec rdx
    jmp .Lmemset1.loop
.Lmemset1.end:
    ret

# void * memcpy(void * d, const void * s, u64 n);
memcpy:
    push rdi
    push rsi
    push rdx
    and rdx, 0xffffffffffffffe0

    call memcpy32

    mov rdi, rax
    mov rsi, rdx
    mov rdx, [rsp]
    and rdx, 0x1f

    call memcpy1

    pop rdx
    pop rsi
    pop rax

    ret

memcpy32:
.Lmemcpy32.loop:
    test rdx, rdx
    jz .Lmemcpy32.end
    sub rdx, 32
    vmovdqu ymm0, YMMWORD PTR [rsi]
    vmovdqu YMMWORD PTR [rdi], ymm0
    add rdi, 32
    add rsi, 32
    jmp .Lmemcpy32.loop
.Lmemcpy32.end:
    mov rax, rdi
    mov rdx, rsi
    ret

memcpy1:
    mov rax, rdi
    mov rcx, rdx
    rep movsb
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
