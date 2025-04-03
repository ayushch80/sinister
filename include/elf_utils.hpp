#ifndef ELF_UTILS_HPP
#define ELF_UTILS_HPP

#include <iostream>

#include "../include/utils.hpp"

class ELF
{
private:
    Buffer elf;

public:
    ELF(Buffer buffer);
    bool isStrippedELF();
    std::string getMagic();
    std::string getClass();
    std::string getData();
    std::string getVersion();
    std::string getOSABI();
    std::string getABIVersion();
    std::string getType();
    std::string getMachine();
    std::string getEntrypoint();
    std::string getPHOffset();
    std::string getSHOffest();
};

#endif // ELF_UTILS_HPP