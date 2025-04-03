#include <iostream>
#include <cstring>
#include <cstdarg>
#include <fstream>

#include "../include/utils.hpp"

Buffer readfile(std::string filepath)
{
    std::ifstream file(filepath, std::ios::binary);
    Buffer res;

    if (!file)
    {
        std::cerr << "Error opening file: " << filepath << std::endl;
        exit(1);
    }

    size_t filesize = 0;
    file.seekg(0, std::ios::end);
    filesize = file.tellg();

    char *buffer = new char[filesize];
    file.seekg(0, std::ios::beg);
    file.read(buffer, filesize);
    if (!file)
    {
        std::cerr << "Error reading file: " << filepath << std::endl;
        delete[] buffer;
        exit(1);
    }
    file.close();

    res.buffer = buffer;
    res.size = filesize;

    return res;
}

bool writefile(std::string filepath, Buffer buffer)
{
    std::ofstream file(filepath, std::ios::binary);
    if (!file)
    {
        std::cerr << "Error opening file for writing: " << filepath << std::endl;
        return false;
    }

    file.write(buffer.buffer, buffer.size);
    if (!file)
    {
        std::cerr << "Error writing to file: " << filepath << std::endl;
        return false;
    }

    file.close();

    return true;
}

/// @brief
/// @param buffer Buffer to read from
/// @return
std::string formatString(const char *fmt, ...)
{
    char buffer[256];
    va_list args;
    va_start(args, fmt);
    std::vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);
    return std::string(buffer);
}

/// @brief
/// @param buffer
/// @param index
/// @param size
/// @return
uint64_t read_le_address(char *buffer, int index, int size) {
    uint64_t value = 0;
    if (size > 8) return 0; // Prevent reading beyond 64-bit

    std::memcpy(&value, buffer + index, size);
    
    return value;
}