#include "internal/io.h"

void puts(const char *str) {
    const char *a = str;
    // Parcurgem sirul pana ajungem la final
    // Scriem caracter cu caracter pe rand, folosind functia write
    // La final adaug un newline
    while (*a) {
        write(1, a++, 1);
    }
    write(1, "\n", 1);
}
