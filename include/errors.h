/*
** EPITECH PROJECT, 2018
** Project nmobjdump
** File description:
** file.
*/

#ifndef NMOBJDUMP_ERRORS_H
#define NMOBJDUMP_ERRORS_H

#include "file_utils.h"

extern const char *program_invocation_name;

void throw_file_not_recognized(file_mapped_t *file);
void throw_file_truncated(file_mapped_t *file);
void throw_malformated_archive(file_mapped_t *file);
void throw_no_symbols(file_mapped_t *file, char *no);

extern const int MY_EXIT_SUCESS;
extern const int MY_EXIT_FAILURE;

#endif //NMOBJDUMP_ERRORS_H
