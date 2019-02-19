/*
** EPITECH PROJECT, 2019
** nmobjdump
** File description:
** compare.c
*/

#include "nm.h"

int nm_compare_64(const void *sym_1, const void *sym_2)
{
    symbol_64_t *comp1 = (symbol_64_t *) sym_1;
    symbol_64_t *comp2 = (symbol_64_t *) sym_2;

    return (strcoll(comp1->sym_name, comp2->sym_name));
}

int nm_compare_32(const void *sym_1, const void *sym_2)
{
    symbol_32_t *comp1 = (symbol_32_t *) sym_1;
    symbol_32_t *comp2 = (symbol_32_t *) sym_2;

    return (strcoll(comp1->sym_name, comp2->sym_name));
}