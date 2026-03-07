# libc's string.h but in x64

Reimplementing some of libc's string functions but in x64 assembly. Runs on linux.

`test.c` uses `-nostdlib`. `art0.s` sets up the main function.

## includes:

- [x] memset
- [x] memcpy
- [x] memmove
- [x] memcmp
- [ ] memchr
- [ ] memccpy
- [ ] strcpy
- [ ] strlen
- [ ] strncpy
- [ ] strcat
- [ ] strncat
- [ ] strspn
- [ ] strpbrk
- [ ] strstr
- [ ] strtok
