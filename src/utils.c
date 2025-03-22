#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "../include/utils.h"

char *readfile (const char *filepath) {
    struct stat st;

    if (stat(filepath, &st) != 0) {
        perror("stat() failed");
        exit(1);
    }

    size_t filesize;
    filesize = st.st_size;

    char *buffer;
    buffer = malloc(filesize);

    if (!buffer) {
        perror("Failed to allocate buffer");
        exit(0);
    }

    FILE *file;
    file = fopen(filepath, "rb");
    
    if (!file) {
        perror(filepath);
        free(buffer);
        exit(1);
    }

    size_t bytesRead;
    bytesRead = fread(buffer, 1, filesize, file);

    fclose(file);

    if (bytesRead != filesize) {
        fprintf(stderr, "Error: Read %zu bytes, expected %zu\n", bytesRead, filesize);
        free(buffer);
        exit(1);
    }

    return buffer;
}