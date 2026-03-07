#define NULL 0

typedef unsigned long long u64;
typedef long long i64;
typedef int i32;
typedef unsigned char u8;

void exit(i32 exit_code);
void println(const char *, const u64 len);

// Returns pointers for "composibility".
// All allocations done on the stack.

// set n bytes to c at s
// i32 because of archaic c history reasons i think
void * memset(const void * s, i32 c, u64 n);

// copy n bytes from s to d. d and s cannot overlap.
void * memcpy(void * d, const void * s, u64 n);

// copy n bytes from s to d. d and s can overlap.
void * memmove(void * d, const void * s, u64 n);

// 0 if s1 == s2, 1 if first differing byte in s1 > s2, else -1
i32 memcmp(const void * s1, const void * s2, u64 n);

// search for unsigned u8 c in first n bytes of s
void * memchr(const void * s, i32 c, u64 n);

// copies first n bytes of s to d until c (unsigned u8). non-overlapping.
void * memccpy(void * d, const void * s, i32 c, u64 n);
