#include <stdio.h>
#include <stdlib.h>

#include "../include/obfuscator.h"
#include "../include/utils.h"

void obfuscate(char *input_filename, char *output_filename)
{

    if (!isSupportedELF(input_filename))
    {
        return;
    }

    Buffer input = readfile(input_filename);
    char *input_buffer = input.buffer;

    {
        printf("ELF HEADER\n");
        printf(" Magic: %s\n", getMagic(input_buffer));
        printf(" Class: %s\n", getClass(input_buffer));
        printf(" Data: %s\n", getData(input_buffer));
        printf(" Version: %s\n", getVersion(input_buffer));
        printf(" OS/ABI: %s\n", getOSABI(input_buffer));
        printf(" ABI Version: %s\n", getABIVersion(input_buffer));
        printf(" Type: %s\n", getType(input_buffer));
        printf(" Machine: %s\n", getMachine(input_buffer));
        printf(" Entry point address: %s\n", getEntrypoint(input_buffer));
        printf(" Program headers offset: %s\n", getPHOffset(input_buffer));
        printf(" Section headers offest: %s\n", getSHOffest(input_buffer));
    }

    Buffer output = input;
    if (!writefile(output_filename, output))
    {
        fprintf(stderr, "Error: Unable to save %s\n", output_filename);
        free(input_buffer);
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("\nSaved %s\n", output_filename);
    }

    free(input_buffer);
}