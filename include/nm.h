/*
** EPITECH PROJECT, 2018
** Project nm
** File description:
** Header file
*/

#ifndef NM_H_
#define NM_H_
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h>
#include <locale.h>

#include "my_elf.h"

typedef struct nm_sec_64_s {
    Elf64_Sym *symbol_tab;
    char *sym_strtab;
    char *sec_strtab;
    uint64_t symbol_nbr;
    uint64_t printable_symbol_nbr;
    Elf64_Shdr *shdr;
} nm_sec_64_t;

typedef struct nm_sec_32_s {
    Elf32_Sym *symbol_tab;
    char *sym_strtab;
    char *sec_strtab;
    uint32_t symbol_nbr;
    uint32_t printable_symbol_nbr;
    Elf32_Shdr *shdr;
} nm_sec_32_t;

typedef struct symbols_64_s {
    char *sym_name;
    Elf64_Addr sym_value;
    unsigned char sym_type;
    Elf64_Section sym_shndx;
} symbol_64_t;

typedef struct symbols_32_s {
    char *sym_name;
    Elf32_Addr sym_value;
    unsigned char sym_type;
    Elf32_Section sym_shndx;
} symbol_32_t;

typedef struct sec_name_to_letter_s {
    const char *section_name;
    unsigned char letter;
} sec_name_to_letter_t;

const int sec_number = 23;

const sec_name_to_letter_t section_to_letter[] = {
    {"*DEBUG*",   'N'},
    {".debug",    'N'},
    {".line",     'N'},
    {".bss",      'b'},
    {"zerovars",  'b'},
    {".zerovars", 'b'},
    {".data",     'd'},
    {"vars",      'd'},
    {".vars",     'd'},
    {".got",      'd'},
    {".plt",      'd'},
    {".dynamic",  'd'},
    {".rdata",    'r'},
    {".rodata",   'r'},
    {".eh_frame", 'r'},
    {".sbss",     's'},
    {".scommun",  'c'},
    {".sdata",    'g'},
    {".text",     't'},
    {"code",      't'},
    {".init",     't'},
    {".fini",     't'},
    {".preinit",  't'}
};

void destroy_file_mapped(file_mapped_t *file);

#endif