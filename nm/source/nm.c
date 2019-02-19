/*
** EPITECH PROJECT, 2019
** nmobjdump
** File description:
** nm.c
*/

#include "archive.h"
#include "errors.h"
#include "nm.h"

int nm_algo_64(file_mapped_t *file, Elf64_Ehdr *hdr)
{
    nm_sec_64_t *nm_sec = get_nm_sec_64(file, hdr);
    symbol_64_t *symbols = NULL;
    unsigned char s_letter;

    if (nm_sec == NULL)
        return (1);
    symbols = get_symbols_64(nm_sec);
    qsort(symbols, nm_sec->printable_symbol_nbr, \
    sizeof(symbol_64_t), &nm_compare_64);
    for (uint64_t y = 0; y < nm_sec->printable_symbol_nbr; y++) {
        if (symbols[y].sym_shndx == SHN_UNDEF)
            printf("%16c", ' ');
        else
            printf("%016x", (unsigned int) symbols[y].sym_value);
        s_letter = get_symbol_type_64(&symbols[y], nm_sec);
        printf(" %c %s\n", s_letter, symbols[y].sym_name);
    }
    return (0);
}

int nm_algo_32(file_mapped_t *file, Elf32_Ehdr *hdr)
{
    nm_sec_32_t *nm_sec = get_nm_sec_32(file, hdr);
    symbol_32_t *symbols = NULL;
    unsigned char s_letter;

    if (nm_sec == NULL)
        return (1);
    symbols = get_symbols_32(nm_sec);
    qsort(symbols, nm_sec->printable_symbol_nbr, \
    sizeof(symbol_32_t), &nm_compare_32);
    for (uint32_t y = 0; y < nm_sec->printable_symbol_nbr; y++) {
        if (symbols[y].sym_shndx == SHN_UNDEF)
            printf("%8c", ' ');
        else
            printf("%08x", (unsigned int) symbols[y].sym_value);
        s_letter = get_symbol_type_32(&symbols[y], nm_sec);
        printf(" %c %s\n", s_letter, symbols[y].sym_name);
    }
    return (0);
}

int launch_nm(file_mapped_t *file, int argc)
{
    int ret = is_32_bit(file, file->load_addr);

    if (ret == 1) {
        if (verify_hdr_32(file, file->load_addr))
            return (1);
        if (argc > 2)
            printf("\n%s:\n", file->file_name);
        nm_algo_32(file, file->load_addr);
    } else if (ret == 0) {
        if (verify_hdr_64(file, file->load_addr))
            return (1);
        if (argc > 2)
            printf("\n%s:\n", file->file_name);
        nm_algo_64(file, file->load_addr);
    } else {
        return (1);
    }
    return (0);
}

int handle_archive_nm(file_mapped_t *file, int argc)
{
    struct ar_hdr *ahdr = file->load_addr + SARMAG;
    char *strtab = NULL;
    file_mapped_t *new_obj = NULL;

    if (file->load_addr + atol(ahdr->ar_size) > \
    file->load_addr + file->size || is_not_reco_archive(file)) {
        throw_file_not_recognized(file);
        return (1);
    }
    ahdr = get_next_file(ahdr, &strtab, file);
    if (argc > 2)
        printf("\n%s:\n", file->file_name);
    for (; ahdr != NULL; ahdr = get_next_file(ahdr, &strtab, file)) {
        if (is_ar_file_mal_formated(ahdr))
            throw_malformated_archive(file);
        new_obj = create_mapped_file_from_archive(ahdr, strtab);
        if (!launch_nm(new_obj, 42))
            destroy_file_mapped(new_obj);
    }
    return (0);
}

int do_nm(char *file_name, int argc)
{
    file_mapped_t *file = NULL;

    if (access(file_name, F_OK)) {
        fprintf(stderr, "%s: '%s': No such file\n", \
        program_invocation_name, file_name);
        return (1);
    } else if ((file = load_file_in_memory(file_name)) == NULL)
        return (1);
    (void) file;
    if (is_archive(file)) {
        if (handle_archive_nm(file, argc))
            return (1);
        else {
            destroy_file_mapped(file);
            return (0);
        }
    } else if (!is_elf_file(file) || launch_nm(file, argc))
        return (1);
    destroy_file_mapped(file);
    return (0);
}