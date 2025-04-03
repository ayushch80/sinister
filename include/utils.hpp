#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <cstddef>

typedef struct
{
    char *buffer; // Buffer to read from
    size_t size;  // Size of the buffer
} Buffer;

Buffer readfile(std::string filepath);
bool writefile(std::string filepath, Buffer buffer);

std::string formatString(const char *fmt, ...);

uint64_t read_le_address(char *buffer, int index, int size);

#endif // UTILS_HPP