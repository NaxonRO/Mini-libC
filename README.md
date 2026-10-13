# Mini-libC

A minimal, **freestanding C standard library** for Linux x86_64, written from scratch on top of raw system calls. It can replace glibc for simple programs. It uses no external library code: every function is built on a single `syscall()` entry point.

## What's implemented

| Area | Functions |
|------|-----------|
| **Strings** (`string.h`) | `strcpy`, `strncpy`, `strcat`, `strncat`, `strcmp`, `strncmp`, `strlen`, `strchr`, `strrchr`, `strstr`, `strrstr` |
| **Memory** (`string.h`) | `memcpy`, `memmove` (overlap-safe), `memcmp`, `memset` |
| **Heap** (`stdlib.h`) | `malloc`, `calloc`, `realloc`, `reallocarray`, `free` |
| **Memory mapping** (`sys/mman.h`) | `mmap`, `mremap`, `munmap` |
| **File I/O** (`fcntl.h`, `unistd.h`) | `open`, `close`, `read`, `write`, `lseek`, `truncate`, `ftruncate` |
| **File status** (`sys/stat.h`) | `stat`, `fstat` |
| **Process / time** | `sleep`, `nanosleep`, `exit` |
| **Output** (`stdio.h`) | `puts` |
| **Errors** | `errno`, set from the negative return values of system calls |

### Design notes
- **System calls:** a variadic `syscall(num, ...)` wrapper forwards up to 6 arguments to the x86_64 `syscall` instruction (`internal/arch/x86_64/syscall_arch.h`). Negative return values are translated into `errno` plus a `-1` return.
- **`malloc`:** every allocation is an anonymous private `mmap`. The block size is stored in a `size_t` header in front of the returned pointer, so `free` and `realloc` know how much to `munmap` or copy.
- **Program startup:** `crt/start.asm` provides `_start`, which calls `__libc_start_main` → `main` → `exit`. Programs link with `-nostdlib`.

## Build & test

Requires `gcc`, `nasm` and `make` on x86_64 Linux.

```bash
cd src && make              # builds libc.a

cd ../samples && make       # sample programs linked against mini-libc instead of glibc
./hello_world

cd ../tests && make check   # test suite (strings, memory, I/O, process)
```

## Repository layout

```
src/string/      string and memory functions
src/mm/          malloc family, mmap wrappers, allocation list
src/io/          open/close/read/write/lseek/truncate/puts
src/stat/        stat/fstat
src/process/     exit, sleep, nanosleep
src/crt/         program entry point (_start)
src/include/     public headers + internal syscall helpers
samples/         example programs
tests/           test suite
```

## Credits

Developed as an assignment for the *Operating Systems* course at the Faculty of Automatic Control and Computers, Politehnica University of Bucharest (2025). The course team provided the skeleton (headers, syscall plumbing, startup code, tests). I implemented the library functions marked as `TODO`: strings, memory, heap allocation, file I/O, stat and sleep.
