/*
** EPITECH PROJECT, 2018
** Project nmobjdump
** File description:
** file.
*/

#ifndef NMOBJDUMP_MY_ELF_H
#define NMOBJDUMP_MY_ELF_H

#include <elf.h>
#include "file_utils.h"

int verify_hdr_64(file_mapped_t *file, Elf64_Ehdr *hdr);
int verify_hdr_32(file_mapped_t *file, Elf32_Ehdr *hdr);
int verify_e_shoff_shnum_64(file_mapped_t *file, Elf64_Ehdr *hdr);
int verify_e_shoff_shnum_32(file_mapped_t *file, Elf32_Ehdr *hdr);
Elf64_Shdr *get_section_header_64(file_mapped_t *file, Elf64_Ehdr *hdr);
Elf32_Shdr *get_section_header_32(file_mapped_t *file, Elf32_Ehdr *hdr);
char *get_sec_strtab_64(file_mapped_t *f, Elf64_Shdr *sh, Elf64_Ehdr *ehdr);
char *get_sec_strtab_32(file_mapped_t *f, Elf32_Shdr *sh, Elf32_Ehdr *ehdr);


int is_elf_file(file_mapped_t *file);
int is_32_bit(file_mapped_t *file, Elf32_Ehdr *hdr);

#endif //NMOBJDUMP_MY_ELF_H
