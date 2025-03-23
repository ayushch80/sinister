#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <stdbool.h>

char *readfile (const char *filepath);
uint64_t read_le_address(char *buffer, int index, int size);
bool isSupportedELF (char *filepath);

#endif // UTILS_H