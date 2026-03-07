#define NULL 0

typedef unsigned long long u64;
typedef long long i64;
typedef int i32;
typedef unsigned char u8;

void exit(i32 exit_code);
void println(const char *, const u64 len);

// Returns pointers for "composibility".

// set n bytes to c at s
// i32 because of archaic c history reasons i think
void * memset(const void * s, i32 c, u64 n);

// copy n bytes from s to d. d and s cannot overlap.
// void * memcpy(void * d, const void * s, size_t n);

// copy n bytes from s to d. d and s can overlap. s saved into
// temp buffer.
// void * memmove(void * d, const void * s, size_t n);

// 0 if s1 == s2, 1 if first differing byte in s1 > s2, else -1
// unsigned u8s.
// i32 memcmp(const void * s1, const void * s2, size_t n);

// search for unsigned u8 c in first n bytes of s
// void * memchr(const void * s, i32 c, size_t n);

// copies first n bytes of s to d until c (unsigned u8). non-overlapping.
// void * memccpy(void * d, const void * s, i32 c, size_t n);

// size_t strlen(const u8 * s);

// return d.
// u8 * strcpy(u8 * d, const u8 * s);

// return d.
// strcpy, copy n bytes to d from s.
// if s < n, pad d with null bytes up to n.
// if d < n, truncated.
// u8 * strncpy(u8 * d, const u8 * s, size_t n);

// d must be big enough. ub otherwise.
// size of d buffer >= strlen(d) + strlen(s) + 1.
// u8 * strcat(u8 * d, u8 * const s);

// append at most n non null bytes of s to d, and null terminate.
// u8 * strncat(u8 * d, const u8 * s, size_t n);

// length in bytes of first s chars that are in accept
// size_t strspn(const char * s, const char * accept);

// pointer to first char of s in accept
// char * strpbrk(const char * s, const char * accept);

// find substring needle in haystack. null bytes obviously not compared.
// return NULL otherwise
// char * strstr(const char * haystack, const char * needle);

// just read manpage.
// char * strtok(char * str, const char * delim);
