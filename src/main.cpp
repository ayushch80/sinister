#include <iostream>
#include <map>
#include <CLI/CLI.hpp>

#include "../include/obfuscator.hpp"

int main(int argc, char **argv)
{
    CLI::App app{"sinister - ELF Obfuscator"};

    app.set_version_flag("-v, --version", "v1.0.0");

    std::string input, output;
    bool verbose = false;

    app.add_option("-i, --input", input, "Input ELF")->required()->option_text("FILE");
    app.add_option("-o, --output", output, "Output ELF")->required()->option_text("FILE");
    app.add_flag("-V, --verbose", verbose, "Verbose output");

    CLI11_PARSE(app, argc, argv);

    arguments arguments;
    arguments.input = input;
    arguments.output = output;
    arguments.verbose = verbose;

    if (verbose)
    {
        std::cout << "[+] Verbose mode enabled" << std::endl;
        std::cout << "[+] Input ELF : " << input << std::endl;
        std::cout << "[+] Output ELF : " << output << std::endl;
        std::cout << std::endl;
    }

    obfuscate(arguments);

    return 0;
}