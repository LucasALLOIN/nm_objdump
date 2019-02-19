/*
** EPITECH PROJECT, 2018
** Project nmobjdump
** File description:
** file.
*/

#include "file_utils.h"
#include "errors.h"

const int MY_EXIT_SUCESS = 0;
const int MY_EXIT_FAILURE = 84;

void throw_file_not_recognized(file_mapped_t *file)
{
    fprintf(stderr, "%s: %s: File format not recognized\n", \
    program_invocation_name, file->file_name);
    destroy_file_mapped(file);
}

void throw_file_truncated(file_mapped_t *file)
{
    fprintf(stderr, "%s: %s: File truncated\n", program_invocation_name, \
    file->file_name);
    destroy_file_mapped(file);
}

void throw_malformated_archive(file_mapped_t *file)
{
    fprintf(stderr, "%s: %s: Malformed archive\n", \
    program_invocation_name, file->file_name);
    destroy_file_mapped(file);
    exit(MY_EXIT_FAILURE);
}

void throw_no_symbols(file_mapped_t *file, char *no)
{
    fprintf(stderr, "%s: %s: %s symbols\n", program_invocation_name, \
    file->file_name, no);
}