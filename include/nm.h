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

int is_valid_offset_64(file_mapped_t *file, Elf64_Off off);
int is_valid_offset_32(file_mapped_t *file, Elf32_Off off);
Elf64_Shdr *get_symbole_hdr_64(file_mapped_t *file, Elf64_Shdr *shdr);
Elf32_Shdr *get_symbole_hdr_32(file_mapped_t *file, Elf32_Shdr *shdr);
int is_valid_symbole_hdr_64(file_mapped_t *file, Elf64_Shdr *shdr);
int is_valid_symbole_hdr_32(file_mapped_t *file, Elf32_Shdr *shdr);
char *get_sym_strtab_64(file_mapped_t *f, Elf64_Shdr *sh, Elf64_Shdr *sym_hdr);
char *get_sym_strtab_32(file_mapped_t *f, Elf32_Shdr *sh, Elf32_Shdr *sym_hdr);
nm_sec_64_t *get_nm_sec_64(file_mapped_t *file, Elf64_Ehdr *ehdr);
nm_sec_32_t *get_nm_sec_32(file_mapped_t *file, Elf32_Ehdr *ehdr);
symbol_64_t *get_symbols_64(nm_sec_64_t *nm_sec);
symbol_32_t *get_symbols_32(nm_sec_32_t *nm_sec);
unsigned char decode_symbol_type_64(symbol_64_t *sym, nm_sec_64_t *nm_sec);
unsigned char decode_symbol_type_32(symbol_32_t *sym, nm_sec_32_t *nm_sec);
unsigned char get_sec_symbol_type_64(symbol_64_t *sym, nm_sec_64_t *nm_sec);
unsigned char get_sec_symbol_type_32(symbol_32_t *sym, nm_sec_32_t *nm_sec);
unsigned char get_weak_symbol_type_64(symbol_64_t *symbol);
unsigned char get_weak_symbol_type_32(symbol_32_t *symbol);
unsigned char get_shndx_symbol_type_64(symbol_64_t *symbol, nm_sec_64_t *nm);
unsigned char get_shndx_symbol_type_32(symbol_32_t *symbol, nm_sec_32_t *nm);
unsigned char get_symbol_type_64(symbol_64_t *symbol, nm_sec_64_t *nm_sec);
unsigned char get_symbol_type_32(symbol_32_t *symbol, nm_sec_32_t *nm_sec);
int nm_compare_64(const void *sym_1, const void *sym_2);
int nm_compare_32(const void *sym_1, const void *sym_2);
int nm_algo_64(file_mapped_t *file, Elf64_Ehdr *hdr);
int nm_algo_32(file_mapped_t *file, Elf32_Ehdr *hdr);
int launch_nm(file_mapped_t *file, int argc);
int handle_archive_nm(file_mapped_t *file, int argc);
int do_nm(char *file_name, int argc);
int main(int argc, char *argv[]);

#endif