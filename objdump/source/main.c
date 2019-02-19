/*
** EPITECH PROJECT, 2018
** Project objdump
** File description:
** Main file.
*/

#include "objdump.h"

const char *ignore_section_array[] = {
    ".bss",
    ".symtab",
    ".strtab",
    ".shstrtab",
    ".rela.eh_frame",
    ".rela.text",
    ".rela.data.rel",
    ".rela.data.rel.local",
    ".rel.eh_frame",
    ".rel.text",
    ".rel.data.rel",
    ".rel.data.rel.local",
    NULL
};

void print_obj_header64(file_mapped_t *file)
{
    Elf64_Ehdr *ehdr = (Elf64_Ehdr *) (file->load_addr);
    Elf64_Shdr *shdr = get_section_header_64(file, ehdr);

    (void) shdr;
    printf("\n%s:     ", file->file_name);
    fflush(NULL);
    printf("file format elf64-x86-64\n");
    printf("architecture: i386:x86-64, flags 0x%08x:\n",
    get_flags64(ehdr, shdr));
    printf_str_flags64(ehdr, shdr);
    printf("start address 0x%016lx\n\n", ehdr->e_entry);
    fflush(NULL);
}

void print_obj_header32(file_mapped_t *file)
{
    Elf32_Ehdr *ehdr = (Elf32_Ehdr *) (file->load_addr);
    Elf32_Shdr *shdr = get_section_header_32(file, ehdr);

    (void) shdr;
    printf("\n%s:     ", file->file_name);
    fflush(NULL);
    printf("file format elf32-i386\n");
    printf("architecture: i386, flags 0x%08x:\n",
    get_flags32(ehdr, shdr));
    printf_str_flags32(ehdr, shdr);
    printf("start address 0x%08x\n\n", ehdr->e_entry);
    fflush(NULL);
}

int is_sec_valid64(Elf64_Shdr *shdr, char *sec_name)
{
    size_t len = 0;

    if (!shdr->sh_size)
        return (0);
    for (int i = 0; ignore_section_array[i] != NULL; i++) {
        len = strlen(ignore_section_array[i]);
        if (strncmp(ignore_section_array[i], sec_name, len) == 0)
            return (0);
    }
    return (1);
}

int is_sec_valid32(Elf32_Shdr *shdr, char *sec_name)
{
    size_t len = 0;

    if (!shdr->sh_size)
        return (0);
    for (int i = 0; ignore_section_array[i] != NULL; i++) {
        len = strlen(ignore_section_array[i]);
        if (strncmp(ignore_section_array[i], sec_name, len) == 0)
            return (0);
    }
    return (1);
}

int main(int argc, char *argv[])
{
    int ret = 0;

    if (argc <= 1)
        return (do_objdump("a.out"));
    for (int i = 1; i < argc; i++) {
        if (ret == 0)
            ret = do_objdump(argv[i]);
        else
            do_objdump(argv[i]);
    }
    return ((ret) ? 84 : 0);
}