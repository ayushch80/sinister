
#include "../include/utils.hpp"
#include "../include/obfuscator.hpp"

void obfuscate(arguments args)
{
    std::string input_filename = args.input;
    std::string output_filename = args.output;

    Buffer input = readfile(input_filename);
    char *input_buffer = input.buffer;

    {
        std::cout << "ELF HEADER" << std::endl;
        std::cout << " Magic: " << getMagic(input_buffer) << std::endl;
        std::cout << " Class: " << getClass(input_buffer) << std::endl;
        std::cout << " Data: " << getData(input_buffer) << std::endl;
        std::cout << " Version: " << getVersion(input_buffer) << std::endl;
        std::cout << " OS/ABI: " << getOSABI(input_buffer) << std::endl;
        std::cout << " ABI Version: " << getABIVersion(input_buffer) << std::endl;
        std::cout << " Type: " << getType(input_buffer) << std::endl;
        std::cout << " Machine: " << getMachine(input_buffer) << std::endl;
        std::cout << " Entry point address: " << getEntrypoint(input_buffer) << std::endl;
        std::cout << " Program headers offset: " << getPHOffset(input_buffer) << std::endl;
        std::cout << " Section headers offest: " << getSHOffest(input_buffer) << std::endl;
        std::cout << std::endl;
    }

    Buffer output = input;

    if (!writefile(output_filename, output))
    {
        std::cerr << "Error: Unable to save " << output_filename << std::endl;
        free(input_buffer);
        exit(1);
    }
    else
    {
        std::cout << "Saved " << output_filename << std::endl;
    }

    free(input_buffer);
}