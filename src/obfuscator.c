#include <stdio.h>
#include <stdlib.h>

#include "../include/obfuscator.h"
#include "../include/utils.h"

void obfuscate(char *input_filename, char *output_filename)
{
    char *input_buffer = readfile(input_filename);

    {
        printf("ELF HEADER\n");
        for (int i = 0; i < 0x40; i++)
        {
            printf("%.2x ", input_buffer[i]);
        }
        printf("\n\n");

        printf("PROGRAM HEADER\n");
        int ph_offset = read_le_address(input_buffer, 0x20, 8);
        printf("Offset : 0x%lx\n", (long)ph_offset);
        for (int i = 0; i < 0x38; i++)
        {
            printf("%.2x ", input_buffer[ph_offset + i]);
        }
        printf("\n\n");

        printf("SECTION HEADER\n");
        int sh_offset = read_le_address(input_buffer, 0x28, 8);
        printf("Offset : 0x%lx\n", (long)sh_offset);
        for (int i = 0; i < 0x40; i++)
        {
            printf("%.2x ", input_buffer[sh_offset + i]);
        }
        printf("\n");
        for (int i = 0x40; i < 0x40 + 0x40; i++)
        {
            printf("%.2x ", input_buffer[sh_offset + i]);
        }
        printf("\n\n");
    }

    if (!isSupportedELF(input_filename))
    {
        return;
    }

    free(input_buffer);
}