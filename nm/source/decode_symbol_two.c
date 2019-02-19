/*
** EPITECH PROJECT, 2019
** nmobjdump
** File description:
** decode_symbole_two.c
*/

#include "nm.h"

const int sec_number = 23;

const sec_name_to_letter_t section_to_letter[] = {
    {"*DEBUG*",   'N'},
    {".debug",    'N'},
    {".line",     'N'},
    {".bss",      'b'},
    {"zerovars",  'b'},
    {".zerovars", 'b'},
    {".data",     'd'},
    {"vars",      'd'},
    {".vars",     'd'},
    {".got",      'd'},
    {".plt",      'd'},
    {".dynamic",  'd'},
    {".rdata",    'r'},
    {".rodata",   'r'},
    {".eh_frame", 'r'},
    {".sbss",     's'},
    {".scommun",  'c'},
    {".sdata",    'g'},
    {".text",     't'},
    {"code",      't'},
    {".init",     't'},
    {".fini",     't'},
    {".preinit",  't'}
};

unsigned char decode_symbol_type_64(symbol_64_t *sym, nm_sec_64_t *nm_sec)
{
    uint64_t f = nm_sec->shdr[sym->sym_shndx].sh_flags;
    uint32_t t = nm_sec->shdr[sym->sym_shndx].sh_type;

    if (t == SHT_PROGBITS && (f & SHF_EXECINSTR) && (f & SHF_ALLOC))
        return ('t');
    else if (t == SHT_NOBITS)
        return ('b');
    (void) t;
    if ((f & SHF_ALLOC) && !(f & SHF_WRITE))
        return ('r');
    else if ((f & SHF_ALLOC) && (f & SHF_WRITE))
        return ('d');
    return ('?');
}

unsigned char decode_symbol_type_32(symbol_32_t *sym, nm_sec_32_t *nm_sec)
{
    uint32_t f = nm_sec->shdr[sym->sym_shndx].sh_flags;
    uint32_t t = nm_sec->shdr[sym->sym_shndx].sh_type;

    if (t == SHT_PROGBITS && (f & SHF_EXECINSTR) && (f & SHF_ALLOC))
        return ('t');
    else if (t == SHT_NOBITS)
        return ('b');
    (void) t;
    if ((f & SHF_ALLOC) && !(f & SHF_WRITE))
        return ('r');
    else if ((f & SHF_ALLOC) && (f & SHF_WRITE))
        return ('d');
    return ('?');
}

unsigned char get_sec_symbol_type_64(symbol_64_t *sym, nm_sec_64_t *nm_sec)
{
    char *sec_name;
    size_t len;
    int type = ELF64_ST_TYPE(sym->sym_type);
    unsigned char res;

    sec_name = nm_sec->sec_strtab + nm_sec->shdr[sym->sym_shndx].sh_name;
    for (int i = 0; i < sec_number; i++) {
        len = strlen(section_to_letter[i].section_name);
        if (strncmp(section_to_letter[i].section_name, sec_name, len) \
        == 0)
            return (section_to_letter[i].letter);
    }
    if ((res = decode_symbol_type_64(sym, nm_sec)) != '?')
        return (res);
    (void) res;
    if (type == STT_FUNC)
        return ('t');
    else if (type == STT_OBJECT || type == STT_NOTYPE)
        return ('d');
    return ('?');
}

unsigned char get_sec_symbol_type_32(symbol_32_t *sym, nm_sec_32_t *nm_sec)
{
    char *sec_name;
    size_t len;
    int type = ELF32_ST_TYPE(sym->sym_type);
    unsigned char res;

    sec_name = nm_sec->sec_strtab + nm_sec->shdr[sym->sym_shndx].sh_name;
    for (int i = 0; i < sec_number; i++) {
        len = strlen(section_to_letter[i].section_name);
        if (strncmp(section_to_letter[i].section_name, sec_name, len) \
        == 0)
            return (section_to_letter[i].letter);
    }
    if ((res = decode_symbol_type_32(sym, nm_sec)) != '?')
        return (res);
    (void) res;
    if (type == STT_FUNC)
        return ('t');
    else if (type == STT_OBJECT || type == STT_NOTYPE)
        return ('d');
    return ('?');
}

unsigned char get_weak_symbol_type_64(symbol_64_t *symbol)
{
    if (symbol->sym_value) {
        if (ELF64_ST_TYPE(symbol->sym_type) == STT_OBJECT)
            return ('V');
        else
            return ('W');
    } else {
        if (ELF64_ST_TYPE(symbol->sym_type) == STT_OBJECT)
            return ('v');
        else
            return ('w');
    }
}