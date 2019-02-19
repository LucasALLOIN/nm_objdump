/*
** EPITECH PROJECT, 2018
** Project nmobjdump
** File description:
** file.
*/

#include "nm.h"
#include "archive.h"
#include "errors.h"

Elf64_Shdr *get_symbole_hdr_64(file_mapped_t *file, Elf64_Shdr *shdr)
{
    Elf64_Ehdr *hdr = file->load_addr;
    Elf64_Shdr *symbol_header = NULL;

    for (uint64_t i = 0; i < hdr->e_shnum; i++) {
        if (shdr[i].sh_type == SHT_SYMTAB)
            symbol_header = &shdr[i];
    }
    if (symbol_header == NULL) {
        throw_no_symbols(file, "no");
        return (NULL);
    } else if (!is_valid_offset_64(file, symbol_header->sh_offset))
        return (NULL);
    return (symbol_header);
}

Elf32_Shdr *get_symbole_hdr_32(file_mapped_t *file, Elf32_Shdr *shdr)
{
    Elf32_Ehdr *hdr = file->load_addr;
    Elf32_Shdr *symbol_header = NULL;

    for (uint32_t i = 0; i < hdr->e_shnum; i++) {
        if (shdr[i].sh_type == SHT_SYMTAB)
            symbol_header = &shdr[i];
    }
    if (symbol_header == NULL) {
        throw_no_symbols(file, "no");
        return (NULL);
    } else if (!is_valid_offset_32(file, symbol_header->sh_offset))
        return (NULL);
    return (symbol_header);
}

nm_sec_64_t *get_nm_sec_64(file_mapped_t *file, Elf64_Ehdr *ehdr)
{
    Elf64_Shdr *shdr = get_section_header_64(file, ehdr);
    Elf64_Shdr *symbol_hdr = get_symbole_hdr_64(file, shdr);
    nm_sec_64_t *nm_sec = my_malloc(sizeof(nm_sec_64_t));

    if (symbol_hdr == NULL || !is_valid_symbole_hdr_64(file, symbol_hdr))
        return (NULL);
    nm_sec->sym_strtab = get_sym_strtab_64(file, shdr, symbol_hdr);
    nm_sec->sec_strtab = get_sec_strtab_64(file, shdr, ehdr);
    nm_sec->symbol_tab = file->load_addr + symbol_hdr->sh_offset;
    nm_sec->symbol_nbr = symbol_hdr->sh_size / sizeof(Elf64_Sym);
    nm_sec->shdr = shdr;
    return (nm_sec);
}

nm_sec_32_t *get_nm_sec_32(file_mapped_t *file, Elf32_Ehdr *ehdr)
{
    Elf32_Shdr *shdr = get_section_header_32(file, ehdr);
    Elf32_Shdr *symbol_hdr = get_symbole_hdr_32(file, shdr);
    nm_sec_32_t *nm_sec = my_malloc(sizeof(nm_sec_32_t));

    if (symbol_hdr == NULL || !is_valid_symbole_hdr_32(file, symbol_hdr))
        return (NULL);
    nm_sec->sym_strtab = get_sym_strtab_32(file, shdr, symbol_hdr);
    nm_sec->sec_strtab = get_sec_strtab_32(file, shdr, ehdr);
    nm_sec->symbol_tab = file->load_addr + symbol_hdr->sh_offset;
    nm_sec->symbol_nbr = symbol_hdr->sh_size / sizeof(Elf32_Sym);
    nm_sec->shdr = shdr;
    return (nm_sec);
}

int main(int argc, char *argv[])
{
    int ret = 0;

    setlocale(LC_ALL, "");
    if (argc <= 1)
        return (do_nm("a.out", argc));
    for (int i = 1; i < argc; i++) {
        if (ret == 0)
            ret = do_nm(argv[i], argc);
        else
            do_nm(argv[i], argc);
    }
    return ((ret) ? 84 : 0);
}