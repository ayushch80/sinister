#include <cstring>

#include "../include/utils.h"

char *getMagic(char *buffer)
{
    std::string magic = "";

    for (int i = 0; i < 16; i++)
    {
        magic = formatString("%s %.2x", stringToCString(magic), buffer[i]);
    }

    return stringToCString(magic);
}

char *getClass(char *buffer)
{
    std::string className = (buffer[4] == 1) ? "32-bit" : "64-bit";
    return stringToCString(className);
}

char *getData(char *buffer)
{
    std::string dataName = (buffer[5] == 1) ? "Little-endian" : "Big-endian";
    return stringToCString(dataName);
}

char *getVersion(char *buffer)
{
    std::string version = formatString("%d", buffer[6]);
    return stringToCString(version);
}

char *stringToCString(std::string str)
{
    char *cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());
    return cstr;
}

std::string formatString(const char *fmt, ...)
{
    char buffer[256];
    va_list args;
    va_start(args, fmt);
    std::vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);
    return std::string(buffer);
}