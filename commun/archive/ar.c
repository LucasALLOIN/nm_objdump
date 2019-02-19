/*
** EPITECH PROJECT, 2018
** Project nmobjdump
** File description:
** file.
*/

#include "archive.h"

const int SAR_STR_TAB = 2;
const char *AR_STR_TAB = "//";
const char AR_END_FILENAME = '/';
const int SAR_F_MAG = 2;

int is_archive(file_mapped_t *file)
{
    if (file->size < SARMAG)
        return (0);
    else if (strncmp(ARMAG, file->load_addr, SARMAG) == 0)
        return (1);
    return (0);
}

file_mapped_t *create_mapped_file_from_archive(struct ar_hdr *ahdr, char *stab)
{
    file_mapped_t *new = my_malloc(sizeof(file_mapped_t));
    char *new_name = NULL;
    char *name_ptr = NULL;
    size_t size = 0;

    if (ahdr->ar_name[0] == AR_END_FILENAME && stab != NULL) {
        name_ptr = (void *) stab + atoi(ahdr->ar_name + 1);
    } else
        name_ptr = ahdr->ar_name;
    for (; name_ptr[size] != AR_END_FILENAME; size++);
    new_name = my_malloc(size + 1);
    strncpy(new_name, name_ptr, size);
    new->file_name = new_name;
    new->load_addr = (void *) ahdr + sizeof(struct ar_hdr);
    new->size = (unsigned int) strtoul(ahdr->ar_size, NULL, 10);
    new->is_ar = 1;
    return (new);
}

struct ar_hdr *get_next_file(struct ar_hdr *ahdr, char **t, file_mapped_t *f)
{
    long size = atol(ahdr->ar_size);
    void *new_file = ((void *) ahdr) + sizeof(struct ar_hdr) + size;

    if (new_file >= f->load_addr + f->size)
        return (NULL);
    if (strncmp(AR_STR_TAB, new_file, SAR_STR_TAB) == 0) {
        *t = new_file + sizeof(struct ar_hdr);
        return (get_next_file(new_file, t, f));
    }
    return (new_file);
}

int is_ar_file_mal_formated(struct ar_hdr *ahdr)
{
    void *end_pt = (void *) ahdr + sizeof(struct ar_hdr) - SAR_F_MAG;

    if (strncmp(ARFMAG, end_pt, SAR_F_MAG) != 0)
        return (1);
    return (0);
}

int is_not_reco_archive(file_mapped_t *file)
{
    struct ar_hdr *ahdr = file->load_addr + SARMAG;
    int size;

    if (is_ar_file_mal_formated(ahdr))
        return (1);
    while ((void *) ahdr < file->load_addr + file->size) {
        if (strncmp(AR_STR_TAB, ahdr->ar_name, SAR_STR_TAB) == 0 && \
        is_ar_file_mal_formated(ahdr))
            return (1);
        size = atoi(ahdr->ar_size);
        ahdr = ((void *) ahdr) + sizeof(struct ar_hdr) + size;
    }
    return (0);
}
