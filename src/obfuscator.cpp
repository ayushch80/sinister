#include "../include/utils.hpp"
#include "../include/elf_utils.hpp"
#include "../include/obfuscator.hpp"

void obfuscate(arguments args)
{
    std::string input_filename = args.input;
    std::string output_filename = args.output;
    bool verbose = args.verbose;

    Buffer input = readfile(input_filename);
    ELF input_elf(input);

    bool strippedELF = false;

    // [VERBOSE] Basic information about the input ELF file
    if (verbose)
    {
        std::cout << "ELF HEADER" << std::endl;
        std::cout << " Magic: " << input_elf.getMagic() << std::endl;
        std::cout << " Class: " << input_elf.getClass() << std::endl;
        std::cout << " Data: " << input_elf.getData() << std::endl;
        std::cout << " Version: " << input_elf.getVersion() << std::endl;
        std::cout << " OS/ABI: " << input_elf.getOSABI() << std::endl;
        std::cout << " ABI Version: " << input_elf.getABIVersion() << std::endl;
        std::cout << " Type: " << input_elf.getType() << std::endl;
        std::cout << " Machine: " << input_elf.getMachine() << std::endl;
        std::cout << " Entry point address: " << input_elf.getEntrypoint() << std::endl;
        std::cout << " Program headers offset: " << input_elf.getPHOffset() << std::endl;
        std::cout << " Section headers offest: " << input_elf.getSHOffest() << std::endl;
        std::cout << std::endl;
    }

    // Check if the ELF file is stripped
    // [VERBOSE] The ELF file is stripped or not
    if (input_elf.isStrippedELF())
    {
        if (verbose)
            std::cout << "The ELF file is stripped." << std::endl;
        strippedELF = true;
    }
    else if (verbose)
    {
        std::cout << "The ELF file is not stripped." << std::endl;
    }

    Buffer output = input;

    if (!writefile(output_filename, output))
    {
        std::cerr << "Error: Unable to save " << output_filename << std::endl;
        exit(1);
    }
    else
    {
        std::cout << "Saved output ELF to " << output_filename << std::endl;
    }
}