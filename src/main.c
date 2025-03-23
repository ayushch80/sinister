#include <stdio.h>
#include <argp.h>

#include "../include/obfuscator.h"

const char *argp_program_version = "Sinister 1.0";
const char *argp_program_bug_address = "<ayushch80@gmail.com>";

static char doc[] = "sinister - An ELF obfuscation engine";
static char args_doc[] = "";

static struct argp_option options[] = {
    {"input", 'i', "FILE", 0, "Specifies input file"},
    {"output", 'o', "FILE", 0, "Specifies output file"},
    {0}};

struct arguments
{
    char *input;  // Input relative filepath
    char *output; // Output relative filepath
};

static error_t parse_opt(int key, char *arg, struct argp_state *state)
{
    struct arguments *arguments = state->input;

    switch (key)
    {
    case 'i': // Input file
        arguments->input = arg;
        break;
    case 'o': // Output file
        arguments->output = arg;
        break;
    default:
        return ARGP_ERR_UNKNOWN; // Unknown flag
    }
    return 0;
}

static struct argp argp = {options, parse_opt, args_doc, doc};

int main(int argc, char **argv)
{
    struct arguments arguments = {0};

    argp_parse(&argp, argc, argv, 0, 0, &arguments);

    // Checks for mandatory flags (input and output files)
    if (!arguments.input)
    {
        fprintf(stderr, "Error: Missing input file. Use -i or --input.\n");
        return 1;
    }
    if (!arguments.output)
    {
        fprintf(stderr, "Error: Missing output file. Use -o or --output.\n");
        return 1;
    }

    // printf("[*] Input File: %s\n", arguments.input);
    // printf("[*] Output File: %s\n", arguments.output);

    obfuscate(arguments.input, arguments.output);

    return 0;
}