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
/// @return Magic number of the ELF file
std::string getMagic(char *buffer)
{
    std::string magic = "";

    for (int i = 0; i < 16; i++)
    {
        magic += formatString("%.2x ", buffer[i]);
    }

    return magic;
}

/// @brief
/// @param buffer Buffer to read from
/// @return Class of the ELF file
std::string getClass(char *buffer)
{
    std::string className = (buffer[4] == 1) ? "32-bit" : "64-bit";
    return className;
}

/// @brief
/// @param buffer Buffer to read from
/// @return
std::string getData(char *buffer)
{
    std::string dataName = (buffer[5] == 1) ? "Little-endian" : "Big-endian";
    return dataName;
}

/// @brief
/// @param buffer Buffer to read from
/// @return
std::string getVersion(char *buffer)
{
    std::string version = formatString("%d", buffer[6]);
    return version;
}

/// @brief
/// @param buffer Buffer to read from
/// @return
std::string getOSABI(char *buffer)
{
    int osabi = buffer[7];
    std::string osabiName = "";
    switch (osabi)
    {
    case 0x00:
        osabiName = "System V";
        break;
    case 0x01:
        osabiName = "HP-UX";
        break;
    case 0x02:
        osabiName = "NetBSD";
        break;
    case 0x03:
        osabiName = "Linux";
        break;
    case 0x06:
        osabiName = "Sun Solaris";
        break;
    case 0x07:
        osabiName = "AIX";
        break;
    case 0x08:
        osabiName = "IRIX";
        break;
    case 0x09:
        osabiName = "FreeBSD";
        break;
    case 0x0A:
        osabiName = "Tru64";
        break;
    case 0x0B:
        osabiName = "Novell Modesto";
        break;
    case 0x0C:
        osabiName = "OpenBSD";
        break;
    case 0x0D:
        osabiName = "OpenVMS";
        break;
    case 0x0E:
        osabiName = "NonStop Kernel";
        break;
    case 0x0F:
        osabiName = "AROS";
        break;
    case 0x10:
        osabiName = "Fenix OS";
        break;
    case 0x11:
        osabiName = "CloudABI";
        break;
    case 0x12:
        osabiName = "Stratus Technologies OpenVOS";
        break;
    case 0x53:
        osabiName = "Sortix";
        break;
    default:
        osabiName = "Unknown";
        break;
    }
    return osabiName;
}

/// @brief
/// @param buffer Buffer to read from
/// @return
std::string getABIVersion(char *buffer)
{
    std::string abiversion = formatString("%d", buffer[8]);
    return abiversion;
}

/// @brief
/// @param buffer Buffer to read from
/// @return
std::string getType(char *buffer)
{
    int type = read_le_address(buffer, 0x10, 2);
    std::string typeName = "";

    switch (type)
    {
    case 0x00:
        typeName = "ET_NONE";
        break;
    case 0x01:
        typeName = "ET_REL";
        break;
    case 0x02:
        typeName = "ET_EXEC";
        break;
    case 0x03:
        typeName = "ET_DYN";
        break;
    case 0x04:
        typeName = "ET_CORE";
        break;
    case 0xFE00:
        typeName = "ET_LOOS";
        break;
    case 0xFEFF:
        typeName = "ET_HIOS";
        break;
    case 0xFF00:
        typeName = "ET_LOPROC";
        break;
    case 0xFFFF:
        typeName = "ET_HIPROC";
        break;
    default:
        typeName = "Unknown";
        break;
    }

    return typeName;
}

/// @brief
/// @param buffer Buffer to read from
/// @return
std::string getMachine(char *buffer)
{
    int value = read_le_address(buffer, 0x12, 2);
    std::string isa = "";

    switch (value)
    {
    case 0x00:
        isa = "No specific instruction set";
        break;
    case 0x01:
        isa = "AT&T WE 32100";
        break;
    case 0x02:
        isa = "SPARC";
        break;
    case 0x03:
        isa = "x86";
        break;
    case 0x04:
        isa = "Motorola 68000 (M68k)";
        break;
    case 0x05:
        isa = "Motorola 88000 (M88k)";
        break;
    case 0x06:
        isa = "Intel MCU";
        break;
    case 0x07:
        isa = "Intel 80860";
        break;
    case 0x08:
        isa = "MIPS";
        break;
    case 0x09:
        isa = "IBM System/370";
        break;
    case 0x0A:
        isa = "MIPS RS3000 Little-endian";
        break;
    case 0x0B:
        isa = "Reserved";
        break;
    case 0x0C:
        isa = "Reserved";
        break;
    case 0x0D:
        isa = "Reserved";
        break;
    case 0x0E:
        isa = "Reserved";
        break;
    case 0x0F:
        isa = "Hewlett-Packard PA-RISC";
        break;
    case 0x13:
        isa = "Intel 80960";
        break;
    case 0x14:
        isa = "PowerPC";
        break;
    case 0x15:
        isa = "PowerPC 64-bit";
        break;
    case 0x16:
        isa = "IBM S390 / IBM S390x";
        break;
    case 0x17:
        isa = "IBM SPU/SPC";
        break;
    case 0x18:
        isa = "Reserved";
        break;
    case 0x19:
        isa = "Reserved";
        break;
    case 0x1A:
        isa = "Reserved";
        break;
    case 0x1B:
        isa = "Reserved";
        break;
    case 0x1C:
        isa = "Reserved";
        break;
    case 0x1D:
        isa = "Reserved";
        break;
    case 0x1E:
        isa = "Reserved";
        break;
    case 0x1F:
        isa = "Reserved";
        break;
    case 0x20:
        isa = "Reserved";
        break;
    case 0x21:
        isa = "Reserved";
        break;
    case 0x22:
        isa = "Reserved";
        break;
    case 0x23:
        isa = "Reserved";
        break;
    case 0x24:
        isa = "NEC V800";
        break;
    case 0x25:
        isa = "Fujitsu FR20";
        break;
    case 0x26:
        isa = "TRW RH-32";
        break;
    case 0x27:
        isa = "Motorola RCE";
        break;
    case 0x28:
        isa = "ARM upto ARMv7/AArch32";
        break;
    case 0x29:
        isa = "Digital Alpha";
        break;
    case 0x2A:
        isa = "SuperH";
        break;
    case 0x2B:
        isa = "SPARC Version 9";
        break;
    case 0x2C:
        isa = "Siemens TriCore embedded processor";
        break;
    case 0x2D:
        isa = "Argonaut RISC Core";
        break;
    case 0x2E:
        isa = "Hitachi H8/300";
        break;
    case 0x2F:
        isa = "Hitachi H8/300H";
        break;
    case 0x30:
        isa = "Hitachi H8S";
        break;
    case 0x31:
        isa = "Hitachi H8/500";
        break;
    case 0x32:
        isa = "Intel IA-64 processor architecture";
        break;
    case 0x33:
        isa = "Stanford MIPS-X";
        break;
    case 0x34:
        isa = "Motorola ColdFire";
        break;
    case 0x35:
        isa = "Motorola M68HC12";
        break;
    case 0x36:
        isa = "Fujitsu MMA Multimedia Accelerator";
        break;
    case 0x37:
        isa = "Siemens PCP";
        break;
    case 0x38:
        isa = "Sony nCPU embedded RISC processor";
        break;
    case 0x39:
        isa = "Denso NDR1 microprocessor";
        break;
    case 0x3A:
        isa = "Motorola Start*Core processor";
        break;
    case 0x3B:
        isa = "Toyota ME16 processor";
        break;
    case 0x3C:
        isa = "STMicroelectronics ST100 processor";
        break;
    case 0x3D:
        isa = "Advanced Logic Corp. TinyJ embedded processor family";
        break;
    case 0x3E:
        isa = "AMD x86-64 architecture";
        break;
    case 0x3F:
        isa = "Sony DSP Processor";
        break;
    case 0x40:
        isa = "Digital Equipment Corp. PDP-10";
        break;
    case 0x41:
        isa = "Digital Equipment Corp. PDP-11";
        break;
    case 0x42:
        isa = "Siemens FX66 microcontroller";
        break;
    case 0x43:
        isa = "STMicroelectronics ST9+ 8/16 bit microcontroller";
        break;
    case 0x44:
        isa = "STMicroelectronics ST7 8-bit microcontroller";
        break;
    case 0x45:
        isa = "Motorola MC68HC16 Microcontroller";
        break;
    case 0x46:
        isa = "Motorola MC68HC11 Microcontroller";
        break;
    case 0x47:
        isa = "Motorola MC68HC08 Microcontroller";
        break;
    case 0x48:
        isa = "Motorola MC68HC05 Microcontroller";
        break;
    case 0x49:
        isa = "Silicon Graphics SVx";
        break;
    case 0x4A:
        isa = "STMicroelectronics ST19 8-bit microcontroller";
        break;
    case 0x4B:
        isa = "Digital VAX";
        break;
    case 0x4C:
        isa = "Axis Communications 32-bit embedded processor";
        break;
    case 0x4D:
        isa = "Infineon Technologies 32-bit embedded processor";
        break;
    case 0x4E:
        isa = "Element 14 64-bit DSP Processor";
        break;
    case 0x4F:
        isa = "LSI Logic 16-bit DSP Processor";
        break;
    case 0x8C:
        isa = "TMS320C6000 Family";
        break;
    case 0xAF:
        isa = "MCST Elbrus e2k";
        break;
    case 0xB7:
        isa = "ARM 64-bits ARMv8/AArch64";
        break;
    case 0xDC:
        isa = "Zilog Z80";
        break;
    case 0xF3:
        isa = "RISC-V";
        break;
    case 0xF7:
        isa = "Berkeley Packet Filter";
        break;
    case 0x101:
        isa = "WDC 65C816";
        break;
    case 0x102:
        isa = "LoongArch";
        break;
    default:
        isa = "Unknown";
        break;
    }

    return isa;
}

/// @brief
/// @param buffer Buffer to read from
/// @return
std::string getEntrypoint(char *buffer)
{
    int entrypoint = read_le_address(buffer, 0x18, 8);
    std::string entrypointStr = formatString("0x%lx", (long)entrypoint);
    return entrypointStr;
}

/// @brief
/// @param buffer Buffer to read from
/// @return
std::string getPHOffset(char *buffer)
{
    std::string offset = formatString("0x%lx", read_le_address(buffer, 0x20, 8));
    return offset;
}

/// @brief
/// @param buffer Buffer to read from
/// @return
std::string getSHOffest(char *buffer)
{
    std::string offset = formatString("0x%lx", read_le_address(buffer, 0x28, 8));
    return offset;
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
uint64_t read_le_address(char *buffer, int index, int size)
{
    uint64_t address = 0;
    for (int i = 0; i < size; i++)
    {
        address |= ((uint64_t)buffer[index + i] << (i * 8));
    }
    return address;
}