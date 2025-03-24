#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <libelf.h>
#include <gelf.h>
#include <fcntl.h>
#include <unistd.h>

#include "../include/utils.h"

char *readfile(const char *filepath)
{
    struct stat st;

    if (stat(filepath, &st) != 0)
    {
        perror("stat() failed");
        exit(EXIT_FAILURE);
    }

    size_t filesize;
    filesize = st.st_size;

    char *buffer;
    buffer = malloc(filesize);

    if (!buffer)
    {
        perror("Failed to allocate buffer");
        exit(EXIT_FAILURE);
    }

    FILE *file;
    file = fopen(filepath, "rb");

    if (!file)
    {
        perror(filepath);
        free(buffer);
        exit(EXIT_FAILURE);
    }

    size_t bytesRead;
    bytesRead = fread(buffer, 1, filesize, file);

    fclose(file);

    if (bytesRead != filesize)
    {
        fprintf(stderr, "Error: Read %zu bytes, expected %zu\n", bytesRead, filesize);
        free(buffer);
        exit(EXIT_FAILURE);
    }

    return buffer;
}

uint64_t read_le_address(char *buffer, int index, int size) {
    uint64_t address = 0;
    for (int i = 0; i < size; i++) {
        address |= ((uint64_t)buffer[index + i] << (i * 8));
    }
    return address;
}

bool isSupportedELF(char *filepath)
{
    if (elf_version(EV_CURRENT) == EV_NONE)
    {
        fprintf(stderr, "ELF library initialization failed\n");
        exit(EXIT_FAILURE);
    }

    int fd;
    Elf *elf;
    GElf_Ehdr ehdr;

    fd = open(filepath, O_RDONLY, 0);
    if (fd < 0)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    elf = elf_begin(fd, ELF_C_READ, NULL);
    if (!elf)
    {
        fprintf(stderr, "elf_begin failed: %s\n", elf_errmsg(-1));
        close(fd);
        exit(EXIT_FAILURE);
    }

    if (gelf_getehdr(elf, &ehdr) != &ehdr)
    {
        fprintf(stderr, "gelf_getehdr failed: %s\n", elf_errmsg(-1));
        elf_end(elf);
        close(fd);
        exit(EXIT_FAILURE);
    }

    if (ehdr.e_ident[EI_CLASS] == ELFCLASS32)
    {
        fprintf(stderr, "32-bit ELF isn't supported yet\n");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("ELF Type: 0x%.2x\n", ehdr.e_type);
    printf("Machine: 0x%.2x\n", ehdr.e_machine);
    printf("Entry point: 0x%lx\n", ehdr.e_entry);
    printf("Program header table offset: 0x%lx\n", ehdr.e_phoff);
    printf("Section header table offset: 0x%lx\n", ehdr.e_shoff);

    elf_end(elf);
    close(fd);
    return true;
}