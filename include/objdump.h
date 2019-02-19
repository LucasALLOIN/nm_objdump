/*
** EPITECH PROJECT, 2018
** Project nm
** File description:
** Header file
*/

#ifndef OBJDUMP_H_
#define OBJDUMP_H_

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include "file_utils.h"
#include "my_elf.h"
#include "archive.h"
#include "errors.h"
#include "flags.h"

int asprintf(char **strp, const char *fmt, ...);;
unsigned int get_flags64(Elf64_Ehdr *ehdr, Elf64_Shdr *shdr);
unsigned int get_flags32(Elf32_Ehdr *ehdr, Elf32_Shdr *shdr);
void printf_str_flags64(Elf64_Ehdr *ehdr, Elf64_Shdr *shdr);
void printf_str_flags32(Elf32_Ehdr *ehdr, Elf32_Shdr *shdr);
void print_obj_header64(file_mapped_t *file);
void print_obj_header32(file_mapped_t *file);
int is_sec_valid64(Elf64_Shdr *shdr, char *sec_name);
int is_sec_valid32(Elf32_Shdr *shdr, char *sec_name);
void print_line_nbr(long int size, unsigned char *t, long int i);
void print_data(long int size, unsigned char *t, long int i);
void print_section_content64(Elf64_Shdr *shdr, file_mapped_t *file);
void print_section_content32(Elf32_Shdr *shdr, file_mapped_t *file);
void objdump64(file_mapped_t *file);
void objdump32(file_mapped_t *file);
int launch_objdump(file_mapped_t *file);
int handle_archive_objdump(file_mapped_t *file);
int do_objdump(char *file_name);
int main(int argc, char *argv[]);

#endif