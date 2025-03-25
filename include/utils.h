#ifndef UTILS_H
#define UTILS_H

#ifdef __cplusplus
#include <iostream>

extern "C"
{
#endif

#include <stdint.h>
#include <stdbool.h>
#include <elf.h>
#include <gelf.h>
#include <stdarg.h>

    // utils.c
    char *readfile(const char *filepath);
    uint64_t read_le_address(char *buffer, int index, int size);
    bool isSupportedELF(char *filepath);

    // utils.cpp
    char *getMagic(char *buffer);
    char *getClass(char *buffer);
    char *getData(char *buffer);
    char *getVersion(char *buffer);
    char *getOSABI(char *buffer);
    char *getABIVersion(char *buffer);
    char *getType(char *buffer);
    char *getMachine(char *buffer);
    char *getEntrypoint(char *buffer);
    char *getPHOffset(char *buffer);
    char *getSHOffest(char *buffer);

#ifdef __cplusplus
}

// utils.cpp
char *stringToCString (std::string str);
std::string formatString(const char *fmt, ...);

#endif

#endif // UTILS_H