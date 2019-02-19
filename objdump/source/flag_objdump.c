/*
** EPITECH PROJECT, 2019
** nmobjdump
** File description:
** flag_objdump.c
*/

#include "objdump.h"

unsigned int get_flags64(Elf64_Ehdr *ehdr, Elf64_Shdr *shdr)
{
    unsigned int flag = BFD_NO_FLAGS;

    if (ehdr->e_type == ET_REL)
        flag |= HAS_RELOC;
    else if (ehdr->e_type == ET_EXEC)
        flag |= EXEC_P;
    for (int i = 0; (i < ehdr->e_shnum); i++)
        if (shdr[i].sh_type == SHT_DYNSYM || shdr[i].sh_type == SHT_SYMTAB) {
            flag |= HAS_SYMS;
            break;
        }
    if (ehdr->e_type == ET_DYN)
        flag |= DYNAMIC;
    for (int i = 0; i < ehdr->e_shnum; i++)
        if (shdr[i].sh_type == SHT_DYNAMIC) {
            flag |= D_PAGED;
            break;
        }
    return flag;
}

unsigned int get_flags32(Elf32_Ehdr *ehdr, Elf32_Shdr *shdr)
{
    unsigned int flag = BFD_NO_FLAGS;

    if (ehdr->e_type == ET_REL)
        flag |= HAS_RELOC;
    else if (ehdr->e_type == ET_EXEC)
        flag |= EXEC_P;
    for (int i = 0; (i < ehdr->e_shnum); i++)
        if (shdr[i].sh_type == SHT_DYNSYM || shdr[i].sh_type == SHT_SYMTAB) {
            flag |= HAS_SYMS;
            break;
        }
    if (ehdr->e_type == ET_DYN)
        flag |= DYNAMIC;
    for (int i = 0; i < ehdr->e_shnum; i++)
        if (shdr[i].sh_type == SHT_DYNAMIC) {
            flag |= D_PAGED;
            break;
        }
    return flag;
}

void printf_str_flags64(Elf64_Ehdr *ehdr, Elf64_Shdr *shdr)
{
    char *str = "";

    if (ehdr->e_type == ET_REL)
        asprintf(&str, "%sHAS_RELOC, ", str);
    else if (ehdr->e_type == ET_EXEC)
        asprintf(&str, "%sEXEC_P, ", str);
    for (int i = 0; (i < ehdr->e_shnum); i++)
        if (shdr[i].sh_type == SHT_DYNSYM || shdr[i].sh_type == SHT_SYMTAB) {
            asprintf(&str, "%sHAS_SYMS, ", str);
            break;
        }
    if (ehdr->e_type == ET_DYN)
        asprintf(&str, "%sDYNAMIC, ", str);
    for (int i = 0; i < ehdr->e_shnum; i++)
        if (shdr[i].sh_type == SHT_DYNAMIC) {
            asprintf(&str, "%sD_PAGED, ", str);
            break;
        }
    str[strlen(str) - 2] = 0;
    printf("%s\n", str);
}

void printf_str_flags32(Elf32_Ehdr *ehdr, Elf32_Shdr *shdr)
{
    char *str = "";

    if (ehdr->e_type == ET_REL)
        asprintf(&str, "%sHAS_RELOC, ", str);
    else if (ehdr->e_type == ET_EXEC)
        asprintf(&str, "%sEXEC_P, ", str);
    for (int i = 0; (i < ehdr->e_shnum); i++)
        if (shdr[i].sh_type == SHT_DYNSYM || shdr[i].sh_type == SHT_SYMTAB) {
            asprintf(&str, "%sHAS_SYMS, ", str);
            break;
        }
    if (ehdr->e_type == ET_DYN)
        asprintf(&str, "%sDYNAMIC, ", str);
    for (int i = 0; i < ehdr->e_shnum; i++)
        if (shdr[i].sh_type == SHT_DYNAMIC) {
            asprintf(&str, "%sD_PAGED, ", str);
            break;
        }
    str[strlen(str) - 2] = 0;
    printf("%s\n", str);
}
