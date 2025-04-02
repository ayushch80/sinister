#include <iostream>
#include <cstddef>

typedef struct {
    char *buffer; // Buffer to read from
    size_t size;  // Size of the buffer
} Buffer;

Buffer readfile(std::string filepath);
bool writefile(std::string filepath, Buffer buffer);

std::string getMagic(char *buffer);
std::string getClass(char *buffer);
std::string getData(char *buffer);
std::string getVersion(char *buffer);
std::string getOSABI(char *buffer);
std::string getABIVersion(char *buffer);
std::string getType(char *buffer);
std::string getMachine(char *buffer);
std::string getEntrypoint(char *buffer);
std::string getPHOffset(char *buffer);
std::string getSHOffest(char *buffer);
std::string formatString(const char *fmt, ...);
uint64_t read_le_address(char *buffer, int index, int size);