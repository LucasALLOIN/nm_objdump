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

#endif