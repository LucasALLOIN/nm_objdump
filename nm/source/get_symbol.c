/*
** EPITECH PROJECT, 2019
** nmobjdump
** File description:
** get_symbol.c
*/

#include "nm.h"

symbol_64_t *get_symbols_64(nm_sec_64_t *nm_sec)
{
    symbol_64_t *symbols = my_malloc((nm_sec->symbol_nbr + 1) *
    sizeof(symbol_64_t));
    uint64_t i = 0;
    char *name;

    for (uint64_t y = 0; y < nm_sec->symbol_nbr; y++) {
        name = nm_sec->sym_strtab + nm_sec->symbol_tab[y].st_name;
        if (nm_sec->symbol_tab[y].st_name != 0 && \
        nm_sec->symbol_tab[y].st_info != STT_FILE) {
            symbols[i].sym_name = name;
            symbols[i].sym_value = nm_sec->symbol_tab[y].st_value;
            symbols[i].sym_type = nm_sec->symbol_tab[y].st_info;
            symbols[i].sym_shndx = nm_sec->symbol_tab[y].st_shndx;
            i++;
        }
    }
    nm_sec->printable_symbol_nbr = i;
    return (symbols);
}

symbol_32_t *get_symbols_32(nm_sec_32_t *nm_sec)
{
    symbol_32_t *symbols = my_malloc((nm_sec->symbol_nbr + 1) *
    sizeof(symbol_32_t));
    uint32_t i = 0;
    char *name;

    for (uint32_t y = 0; y < nm_sec->symbol_nbr; y++) {
        name = nm_sec->sym_strtab + nm_sec->symbol_tab[y].st_name;
        if (nm_sec->symbol_tab[y].st_name != 0 && \
        nm_sec->symbol_tab[y].st_info != STT_FILE) {
            symbols[i].sym_name = name;
            symbols[i].sym_value = nm_sec->symbol_tab[y].st_value;
            symbols[i].sym_type = nm_sec->symbol_tab[y].st_info;
            symbols[i].sym_shndx = nm_sec->symbol_tab[y].st_shndx;
            i++;
        }
    }
    nm_sec->printable_symbol_nbr = i;
    return (symbols);
}

char *get_sym_strtab_64(file_mapped_t *f, Elf64_Shdr *sh, Elf64_Shdr *sym_hdr)
{
    return (f->load_addr + sh[sym_hdr->sh_link].sh_offset);
}

char *get_sym_strtab_32(file_mapped_t *f, Elf32_Shdr *sh, Elf32_Shdr *sym_hdr)
{
    return (f->load_addr + sh[sym_hdr->sh_link].sh_offset);
}