/*
** EPITECH PROJECT, 2019
** nmobjdump
** File description:
** decode_symbol_one.c
*/

#include "nm.h"

unsigned char get_weak_symbol_type_32(symbol_32_t *symbol)
{
    if (symbol->sym_value) {
        if (ELF32_ST_TYPE(symbol->sym_type) == STT_OBJECT)
            return ('V');
        else
            return ('W');
    } else {
        if (ELF32_ST_TYPE(symbol->sym_type) == STT_OBJECT)
            return ('v');
        else
            return ('w');
    }
}

unsigned char get_shndx_symbol_type_64(symbol_64_t *symbol, nm_sec_64_t *nm)
{
    unsigned char t;

    if (symbol->sym_shndx == SHN_ABS)
        t = 'a';
    else if (symbol->sym_shndx)
        t = get_sec_symbol_type_64(symbol, nm);
    else
        return ('?');
    return (t);
}

unsigned char get_shndx_symbol_type_32(symbol_32_t *symbol, nm_sec_32_t *nm)
{
    unsigned char t;

    if (symbol->sym_shndx == SHN_ABS)
        t = 'a';
    else if (symbol->sym_shndx)
        t = get_sec_symbol_type_32(symbol, nm);
    else
        return ('?');
    return (t);
}

unsigned char get_symbol_type_64(symbol_64_t *symbol, nm_sec_64_t *nm_sec)
{
    int st_bind = ELF64_ST_BIND(symbol->sym_type);
    unsigned char t;

    if (st_bind == STB_WEAK)
        return (get_weak_symbol_type_64(symbol));
    switch (symbol->sym_shndx) {
        case SHN_COMMON:
            return ('C');
        case SHN_UNDEF:
            return ('U');
        case SHN_XINDEX:
            return ('I');
    };
    if (st_bind != STB_GLOBAL && st_bind != STB_LOCAL)
        return ('?');
    t = get_shndx_symbol_type_64(symbol, nm_sec);
    if (st_bind == STB_GLOBAL && t != '?')
        t = (unsigned char) toupper(t);
    return (t);
}

unsigned char get_symbol_type_32(symbol_32_t *symbol, nm_sec_32_t *nm_sec)
{
    int st_bind = ELF32_ST_BIND(symbol->sym_type);
    unsigned char t;

    if (st_bind == STB_WEAK)
        return (get_weak_symbol_type_32(symbol));
    switch (symbol->sym_shndx) {
        case SHN_COMMON:
            return ('C');
        case SHN_UNDEF:
            return ('U');
        case SHN_XINDEX:
            return ('I');
    };
    if (st_bind != STB_GLOBAL && st_bind != STB_LOCAL)
        return ('?');
    t = get_shndx_symbol_type_32(symbol, nm_sec);
    if (st_bind == STB_GLOBAL && t != '?')
        t = (unsigned char) toupper(t);
    return (t);
}