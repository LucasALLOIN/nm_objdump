/*
** EPITECH PROJECT, 2019
** nmobjdump
** File description:
** printf_section.c
*/

#include "objdump.h"

void print_line_nbr(long int size, unsigned char *t, long int i)
{
    for (long int x = 0; x < 16; x++) {
        if (x % 4 == 0 && x != 0)
            printf(" ");
        if ((((i * 16) + x) >= size))
            printf("  ");
        else
            printf("%02x", t[(i * 16) + x]);
    }
}

void print_data(long int size, unsigned char *t, long int i)
{
    for (long int x = 0; x < 16; x++)
        if ((((i * 16) + x) >= size))
            printf(" ");
        else
            printf("%c", isprint(t[(i * 16) + x]) ? t[(i * 16) + x] : '.');

}

void print_section_content64(Elf64_Shdr *shdr, file_mapped_t *file)
{
    Elf64_Xword size = shdr->sh_size;
    unsigned char *t = ((unsigned char *) file->load_addr + shdr->sh_offset);
    unsigned long value = shdr->sh_addr;

    for (Elf64_Xword i = 0; (i * 16) < size; i++) {
        printf(" %0*lx ",
        ((int) (log(i) / log(16)) > 4) ? (int) (log(i) / log(16)) : 4,
        (value + i * 16));
        print_line_nbr(size, t, i);
        printf("  ");
        print_data(size, t, i);
        printf("\n");
        fflush(NULL);
    }
}

void print_section_content32(Elf32_Shdr *shdr, file_mapped_t *file)
{
    Elf32_Xword size = shdr->sh_size;
    unsigned char *t = ((unsigned char *) file->load_addr + shdr->sh_offset);
    unsigned long value = shdr->sh_addr;

    for (Elf32_Xword i = 0; (i * 16) < size; i++) {
        printf(" %0*lx ",
        ((int) (log(i) / log(16)) > 4) ? (int) (log(i) / log(16)) : 4,
        (value + i * 16));
        print_line_nbr(size, t, i);
        printf("  ");
        print_data(size, t, i);
        printf("\n");
        fflush(NULL);
    }
}