#include <iostream>

typedef struct {
    std::string input;  // Input relative filepath
    std::string output; // Output relative filepath
    int verbose;  // Verbose flag
} arguments;

void obfuscate(arguments args);