/*
** EPITECH PROJECT, 2019
** nmobjdump
** File description:
** errors.c
*/

#include "nm.h"
#include "errors.h"

int is_valid_offset_64(file_mapped_t *file, Elf64_Off off)
{
    if (off > file->size) {
        throw_no_symbols(file, "No");
        destroy_file_mapped(file);
        exit(MY_EXIT_FAILURE);
    }
    return (1);
}

int is_valid_offset_32(file_mapped_t *file, Elf32_Off off)
{
    if (off > file->size) {
        throw_no_symbols(file, "No");
        destroy_file_mapped(file);
        exit(MY_EXIT_FAILURE);
    }
    return (1);
}

int is_valid_symbole_hdr_64(file_mapped_t *file, Elf64_Shdr *shdr)
{
    if (shdr->sh_size / sizeof(Elf64_Sym) == 0) {
        throw_no_symbols(file, "no");
        return (0);
    }
    return (1);
}

int is_valid_symbole_hdr_32(file_mapped_t *file, Elf32_Shdr *shdr)
{
    if (shdr->sh_size / sizeof(Elf32_Sym) == 0) {
        throw_no_symbols(file, "no");
        return (0);
    }
    return (1);
}