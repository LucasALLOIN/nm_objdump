/*
** EPITECH PROJECT, 2019
** nmobjdump
** File description:
** objdump.c
*/

#include "objdump.h"

void objdump64(file_mapped_t *file)
{
    Elf64_Ehdr *ehdr = (Elf64_Ehdr *) (file->load_addr);
    Elf64_Shdr *shdr = get_section_header_64(file, ehdr);
    char *sec_strtab = get_sec_strtab_64(file, shdr, ehdr);
    char *sec_name;

    print_obj_header64(file);
    for (int i = 0; i < ehdr->e_shnum; i++) {
        sec_name = sec_strtab + shdr[i].sh_name;
        if (!is_sec_valid64(&shdr[i], sec_name))
            continue;
        printf("Contents of section %s:\n", sec_name);
        print_section_content64(&shdr[i], file);
    }
}

void objdump32(file_mapped_t *file)
{
    Elf32_Ehdr *ehdr = (Elf32_Ehdr *) (file->load_addr);
    Elf32_Shdr *shdr = get_section_header_32(file, ehdr);
    char *sec_strtab = get_sec_strtab_32(file, shdr, ehdr);
    char *sec_name;

    print_obj_header32(file);
    for (int i = 0; i < ehdr->e_shnum; i++) {
        sec_name = sec_strtab + shdr[i].sh_name;
        if (!is_sec_valid32(&shdr[i], sec_name))
            continue;
        printf("Contents of section %s:\n", sec_name);
        print_section_content32(&shdr[i], file);
    }
}

int launch_objdump(file_mapped_t *file)
{
    int ret = is_32_bit(file, file->load_addr);

    if (ret == 1) {
        if (verify_hdr_32(file, file->load_addr))
            return (1);
        objdump32(file);
    } else if (ret == 0) {
        if (verify_hdr_64(file, file->load_addr))
            return (1);
        objdump64(file);
    } else {
        return (1);
    }
    return (0);
}

int handle_archive_objdump(file_mapped_t *file)
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
    printf("In archive %s:\n", file->file_name);
    fflush(NULL);
    for (; ahdr != NULL; ahdr = get_next_file(ahdr, &strtab, file)) {
        if (is_ar_file_mal_formated(ahdr))
            throw_malformated_archive(file);
        new_obj = create_mapped_file_from_archive(ahdr, strtab);
        (void) new_obj;
        if (!launch_objdump(new_obj))
            destroy_file_mapped(new_obj);
    }
    return (0);
}

int do_objdump(char *file_name)
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
        if (handle_archive_objdump(file))
            return (1);
        else {
            destroy_file_mapped(file);
            return (0);
        }
    } else if (!is_elf_file(file) || launch_objdump(file))
        return (1);
    destroy_file_mapped(file);
    return (0);
}