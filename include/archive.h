/*
** EPITECH PROJECT, 2018
** Project nm
** File description:
** Header file
*/

#ifndef ARCHIVEA_H_
#define ARCHIVEA_H_

#include "string.h"
#include "file_utils.h"
#include <ar.h>

int is_archive(file_mapped_t *file);
file_mapped_t *create_mapped_file_from_archive(struct ar_hdr *hdr, char *tstr);
struct ar_hdr *get_next_file(struct ar_hdr *ahdr, char **t, file_mapped_t *f);
int is_ar_file_mal_formated(struct ar_hdr *ahdr);
int is_not_reco_archive(file_mapped_t *file);

extern const int SAR_STR_TAB;
extern const char *AR_STR_TAB;
extern const char AR_END_FILENAME;
extern const int SAR_F_MAG;

#endif