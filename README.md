# libc's string.h but in x64

Reimplementing some of libc's string functions but in x64 assembly. Runs on linux. Expects System V ABI.

`test.c` uses `-nostdlib`. `art0.s` sets up the main function.

## includes:

- [x] memset
- [x] memcpy
- [x] memmove
- [x] memcmp
- [x] memchr
- [x] memccpy
