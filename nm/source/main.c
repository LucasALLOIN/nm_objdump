/*
** EPITECH PROJECT, 2018
** Project nmobjdump
** File description:
** file.
*/

#include "nm.h"
#include "archive.h"
#include "errors.h"

int is_valid_offset_64(file_mapped_t *file, Elf64_Off off)
{
	if (off > file->size) {
		throw_no_symbols(file, "No");
		destroy_file_mapped(file);
		exit(MY_EXIT_FAILURE);
	}
	return (1);
}

int is_valid_offset_32(file_mapped_t *file, Elf32_Off off)
{
	if (off > file->size) {
		throw_no_symbols(file, "No");
		destroy_file_mapped(file);
		exit(MY_EXIT_FAILURE);
	}
	return (1);
}

Elf64_Shdr *get_symbole_hdr_64(file_mapped_t *file, Elf64_Shdr *shdr)
{
	Elf64_Ehdr *hdr = file->load_addr;
	Elf64_Shdr *symbol_header = NULL;

	for (uint64_t i = 0; i < hdr->e_shnum; i++) {
		if (shdr[i].sh_type == SHT_SYMTAB)
			symbol_header = &shdr[i];
	}
	if (symbol_header == NULL) {
		throw_no_symbols(file, "no");
		return (NULL);
	} else if (!is_valid_offset_64(file, symbol_header->sh_offset))
		return (NULL);
	return (symbol_header);
}

Elf32_Shdr *get_symbole_hdr_32(file_mapped_t *file, Elf32_Shdr *shdr)
{
	Elf32_Ehdr *hdr = file->load_addr;
	Elf32_Shdr *symbol_header = NULL;

	for (uint32_t i = 0; i < hdr->e_shnum; i++) {
		if (shdr[i].sh_type == SHT_SYMTAB)
			symbol_header = &shdr[i];
	}
	if (symbol_header == NULL) {
		throw_no_symbols(file, "no");
		return (NULL);
	} else if (!is_valid_offset_32(file, symbol_header->sh_offset))
		return (NULL);
	return (symbol_header);
}

int is_valid_symbole_hdr_64(file_mapped_t *file, Elf64_Shdr *shdr)
{
	if (shdr->sh_size / sizeof(Elf64_Sym) == 0) {
		throw_no_symbols(file, "no");
		return (0);
	}
	return (1);
}

int is_valid_symbole_hdr_32(file_mapped_t *file, Elf32_Shdr *shdr)
{
	if (shdr->sh_size / sizeof(Elf32_Sym) == 0) {
		throw_no_symbols(file, "no");
		return (0);
	}
	return (1);
}

char *get_sym_strtab_64(file_mapped_t *f, Elf64_Shdr *sh, Elf64_Shdr *sym_hdr)
{
	return (f->load_addr + sh[sym_hdr->sh_link].sh_offset);
}

char *get_sym_strtab_32(file_mapped_t *f, Elf32_Shdr *sh, Elf32_Shdr *sym_hdr)
{
	return (f->load_addr + sh[sym_hdr->sh_link].sh_offset);
}

nm_sec_64_t *get_nm_sec_64(file_mapped_t *file, Elf64_Ehdr *ehdr)
{
	Elf64_Shdr *shdr = get_section_header_64(file, ehdr);
	Elf64_Shdr *symbol_hdr = get_symbole_hdr_64(file, shdr);
	nm_sec_64_t *nm_sec = my_malloc(sizeof(nm_sec_64_t));

	if (symbol_hdr == NULL || !is_valid_symbole_hdr_64(file, symbol_hdr))
		return (NULL);
	nm_sec->sym_strtab = get_sym_strtab_64(file, shdr, symbol_hdr);
	nm_sec->sec_strtab = get_sec_strtab_64(file, shdr, ehdr);
	nm_sec->symbol_tab = file->load_addr + symbol_hdr->sh_offset;
	nm_sec->symbol_nbr = symbol_hdr->sh_size / sizeof(Elf64_Sym);
	nm_sec->shdr = shdr;
	return (nm_sec);
}

nm_sec_32_t *get_nm_sec_32(file_mapped_t *file, Elf32_Ehdr *ehdr)
{
	Elf32_Shdr *shdr = get_section_header_32(file, ehdr);
	Elf32_Shdr *symbol_hdr = get_symbole_hdr_32(file, shdr);
	nm_sec_32_t *nm_sec = my_malloc(sizeof(nm_sec_32_t));

	if (symbol_hdr == NULL || !is_valid_symbole_hdr_32(file, symbol_hdr))
		return (NULL);
	nm_sec->sym_strtab = get_sym_strtab_32(file, shdr, symbol_hdr);
	nm_sec->sec_strtab = get_sec_strtab_32(file, shdr, ehdr);
	nm_sec->symbol_tab = file->load_addr + symbol_hdr->sh_offset;
	nm_sec->symbol_nbr = symbol_hdr->sh_size / sizeof(Elf32_Sym);
	nm_sec->shdr = shdr;
	return (nm_sec);
}

symbol_64_t *get_symbols_64(nm_sec_64_t *nm_sec)
{
	symbol_64_t *symbols = my_malloc((nm_sec->symbol_nbr + 1) *
	sizeof(symbol_64_t));
	uint64_t i = 0;
	char *name;

	for (uint64_t y = 0; y < nm_sec->symbol_nbr; y++) {
		name = nm_sec->sym_strtab + nm_sec->symbol_tab[y].st_name;
		if (nm_sec->symbol_tab[y].st_name != 0 && \
		nm_sec->symbol_tab[y].st_info != STT_FILE) {
			symbols[i].sym_name = name;
			symbols[i].sym_value = nm_sec->symbol_tab[y].st_value;
			symbols[i].sym_type = nm_sec->symbol_tab[y].st_info;
			symbols[i].sym_shndx = nm_sec->symbol_tab[y].st_shndx;
			i++;
		}
	}
	nm_sec->printable_symbol_nbr = i;
	return (symbols);
}

symbol_32_t *get_symbols_32(nm_sec_32_t *nm_sec)
{
	symbol_32_t *symbols = my_malloc((nm_sec->symbol_nbr + 1) *
	sizeof(symbol_32_t));
	uint32_t i = 0;
	char *name;

	for (uint32_t y = 0; y < nm_sec->symbol_nbr; y++) {
		name = nm_sec->sym_strtab + nm_sec->symbol_tab[y].st_name;
		if (nm_sec->symbol_tab[y].st_name != 0 && \
		nm_sec->symbol_tab[y].st_info != STT_FILE) {
			symbols[i].sym_name = name;
			symbols[i].sym_value = nm_sec->symbol_tab[y].st_value;
			symbols[i].sym_type = nm_sec->symbol_tab[y].st_info;
			symbols[i].sym_shndx = nm_sec->symbol_tab[y].st_shndx;
			i++;
		}
	}
	nm_sec->printable_symbol_nbr = i;
	return (symbols);
}

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
	if ((res = decode_symbol_type_32(sym, nm_sec))  != '?')
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

int nm_algo_64(file_mapped_t *file, Elf64_Ehdr *hdr)
{
	nm_sec_64_t *nm_sec = get_nm_sec_64(file, hdr);
	symbol_64_t *symbols = NULL;
	unsigned char s_letter;

	if (nm_sec == NULL)
		return (1);
	symbols = get_symbols_64(nm_sec);
	qsort(symbols, nm_sec->printable_symbol_nbr, \
	sizeof(symbol_64_t), &nm_compare_64);
	for (uint64_t y = 0; y < nm_sec->printable_symbol_nbr; y++) {
		if (symbols[y].sym_shndx == SHN_UNDEF)
			printf("%16c", ' ');
		else
			printf("%016x", (unsigned int) symbols[y].sym_value);
		s_letter = get_symbol_type_64(&symbols[y], nm_sec);
		printf(" %c %s\n", s_letter, symbols[y].sym_name);
	}
	return (0);
}

int nm_algo_32(file_mapped_t *file, Elf32_Ehdr *hdr)
{
	nm_sec_32_t *nm_sec = get_nm_sec_32(file, hdr);
	symbol_32_t *symbols = NULL;
	unsigned char s_letter;

	if (nm_sec == NULL)
		return (1);
	symbols = get_symbols_32(nm_sec);
	qsort(symbols, nm_sec->printable_symbol_nbr, \
	sizeof(symbol_32_t), &nm_compare_32);
	for (uint32_t y = 0; y < nm_sec->printable_symbol_nbr; y++) {
		if (symbols[y].sym_shndx == SHN_UNDEF)
			printf("%8c", ' ');
		else
			printf("%08x", (unsigned int) symbols[y].sym_value);
		s_letter = get_symbol_type_32(&symbols[y], nm_sec);
		printf(" %c %s\n", s_letter, symbols[y].sym_name);
	}
	return (0);
}

int launch_nm(file_mapped_t *file, int argc)
{
	int ret = is_32_bit(file, file->load_addr);

	if (ret == 1) {
		if (verify_hdr_32(file, file->load_addr))
			return (1);
		if (argc > 2)
			printf("\n%s:\n", file->file_name);
		nm_algo_32(file, file->load_addr);
	} else if (ret == 0) {
		if (verify_hdr_64(file, file->load_addr))
			return (1);
		if (argc > 2)
			printf("\n%s:\n", file->file_name);
		nm_algo_64(file, file->load_addr);
	} else {
		return (1);
	}
	return (0);
}

int handle_archive_nm(file_mapped_t *file, int argc)
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
	if (argc > 2)
		printf("\n%s:\n", file->file_name);
	for (; ahdr != NULL; ahdr = get_next_file(ahdr, &strtab, file)) {
		if (is_ar_file_mal_formated(ahdr))
			throw_malformated_archive(file);
		new_obj = create_mapped_file_from_archive(ahdr, strtab);
		if (!launch_nm(new_obj, 42))
			destroy_file_mapped(new_obj);
	}
	return (0);
}

int do_nm(char *file_name, int argc)
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
		if (handle_archive_nm(file, argc))
			return (1);
		else {
			destroy_file_mapped(file);
			return (0);
		}
	} else if (!is_elf_file(file) || launch_nm(file, argc))
		return (1);
	destroy_file_mapped(file);
	return (0);
}

int main(int argc, char *argv[])
{
	int ret = 0;

	setlocale(LC_ALL, "");
	if (argc <= 1)
		return (do_nm("a.out", argc));
	for (int i = 1; i < argc; i++) {
		if (ret == 0)
			ret = do_nm(argv[i], argc);
		else
			do_nm(argv[i], argc);
	}
	return ((ret) ? 84 : 0);
}