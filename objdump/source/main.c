/*
** EPITECH PROJECT, 2018
** Project objdump
** File description:
** Main file.
*/

#include <ctype.h>
#include <math.h>
#include "file_utils.h"
#include "my_elf.h"
#include "archive.h"
#include "errors.h"
#include "objdump.h"
#include "flags.h"

int asprintf(char **strp, const char *fmt, ...);

unsigned int get_flags64(Elf64_Ehdr *ehdr, Elf64_Shdr *shdr)
{
	unsigned int flag = BFD_NO_FLAGS;

	if (ehdr->e_type == ET_REL)
		flag |= HAS_RELOC;
	else if (ehdr->e_type == ET_EXEC)
		flag |= EXEC_P;
	for (int i = 0; (i < ehdr->e_shnum); i++)
		if (shdr[i].sh_type == SHT_DYNSYM || shdr[i].sh_type == SHT_SYMTAB) {
			flag |= HAS_SYMS;
			break;
		}
	if (ehdr->e_type == ET_DYN)
		flag |= DYNAMIC;
	for (int i = 0; i < ehdr->e_shnum; i++)
		if (shdr[i].sh_type == SHT_DYNAMIC) {
			flag |= D_PAGED;
			break;
		}
	return flag;
}

unsigned int get_flags32(Elf32_Ehdr *ehdr, Elf32_Shdr *shdr)
{
    unsigned int flag = BFD_NO_FLAGS;

    if (ehdr->e_type == ET_REL)
        flag |= HAS_RELOC;
    else if (ehdr->e_type == ET_EXEC)
        flag |= EXEC_P;
    for (int i = 0; (i < ehdr->e_shnum); i++)
        if (shdr[i].sh_type == SHT_DYNSYM || shdr[i].sh_type == SHT_SYMTAB) {
            flag |= HAS_SYMS;
            break;
        }
    if (ehdr->e_type == ET_DYN)
        flag |= DYNAMIC;
    for (int i = 0; i < ehdr->e_shnum; i++)
        if (shdr[i].sh_type == SHT_DYNAMIC) {
            flag |= D_PAGED;
            break;
        }
    return flag;
}

void printf_str_flags64(Elf64_Ehdr *ehdr, Elf64_Shdr *shdr)
{
	char *str = "";

	if (ehdr->e_type == ET_REL)
		asprintf(&str, "%sHAS_RELOC, ", str);
	else if (ehdr->e_type == ET_EXEC)
		asprintf(&str, "%sEXEC_P, ", str);
	for (int i = 0; (i < ehdr->e_shnum); i++)
		if (shdr[i].sh_type == SHT_DYNSYM || shdr[i].sh_type == SHT_SYMTAB) {
			asprintf(&str, "%sHAS_SYMS, ", str);
			break;
		}
	if (ehdr->e_type == ET_DYN)
		asprintf(&str, "%sDYNAMIC, ", str);
	for (int i = 0; i < ehdr->e_shnum; i++)
		if (shdr[i].sh_type == SHT_DYNAMIC) {
			asprintf(&str, "%sD_PAGED, ", str);
			break;
		}
	str[strlen(str) - 2] = 0;
	printf("%s\n", str);
}

void printf_str_flags32(Elf32_Ehdr *ehdr, Elf32_Shdr *shdr)
{
    char *str = "";

    if (ehdr->e_type == ET_REL)
        asprintf(&str, "%sHAS_RELOC, ", str);
    else if (ehdr->e_type == ET_EXEC)
        asprintf(&str, "%sEXEC_P, ", str);
    for (int i = 0; (i < ehdr->e_shnum); i++)
        if (shdr[i].sh_type == SHT_DYNSYM || shdr[i].sh_type == SHT_SYMTAB) {
            asprintf(&str, "%sHAS_SYMS, ", str);
            break;
        }
    if (ehdr->e_type == ET_DYN)
        asprintf(&str, "%sDYNAMIC, ", str);
    for (int i = 0; i < ehdr->e_shnum; i++)
        if (shdr[i].sh_type == SHT_DYNAMIC) {
            asprintf(&str, "%sD_PAGED, ", str);
            break;
        }
    str[strlen(str) - 2] = 0;
    printf("%s\n", str);
}

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

void print_section_content64(Elf64_Shdr *shdr, file_mapped_t *file)
{
	Elf64_Xword size = shdr->sh_size;
	unsigned char *t = ((unsigned char *) file->load_addr + shdr->sh_offset);
	unsigned long value = shdr->sh_addr;

	for (Elf64_Xword i = 0; (i * 16) < size; i++) {
        printf(" %0*lx ", ((int) (log(i) / log(16)) > 4) ? (int) (log(i) / log(16)) : 4,(value +i * 16));
		for (Elf64_Xword x = 0; x < 16; x++) {
			if (x % 4 == 0 && x != 0)
				printf(" ");
			if ((((i * 16) + x) >= size))
				printf("  ");
			else
				printf("%02x", t[(i * 16) + x]);
		}
		printf("  ");
		for (Elf64_Xword x = 0; x < 16; x++)
			if ((((i * 16) + x) >= size))
				printf(" ");
			else
				printf("%c", isprint(t[(i * 16) + x]) ? t[(i * 16) + x] : '.');
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
        printf(" %0*lx ", ((int) (log(i) / log(16)) > 4) ? (int) (log(i) / log(16)) : 4,(value +i * 16));
        for (Elf32_Xword x = 0; x < 16; x++) {
            if (x % 4 == 0 && x != 0)
                printf(" ");
            if ((((i * 16) + x) >= size))
                printf("  ");
            else
                printf("%02x", t[(i * 16) + x]);
        }
        printf("  ");
        for (Elf32_Xword x = 0; x < 16; x++)
            if ((((i * 16) + x) >= size))
                printf(" ");
            else
                printf("%c", isprint(t[(i * 16) + x]) ? t[(i * 16) + x] : '.');
        printf("\n");
        fflush(NULL);
    }
}

void objdump64(file_mapped_t *file)
{
	Elf64_Ehdr *ehdr = (Elf64_Ehdr *) (file->load_addr);
	Elf64_Shdr *shdr = get_section_header_64(file, ehdr);
	char *sec_strtab = get_sec_strtab_64(file, shdr, ehdr);
	char *sec_name;

	print_obj_header64(file);
	for (int i = 0; i < ehdr->e_shnum; i++) {
		sec_name = sec_strtab + shdr[i].sh_name;
		if (!is_sec_valid64(&shdr[i], sec_name))
			continue;
		printf("Contents of section %s:\n", sec_name);
		print_section_content64(&shdr[i], file);
	}
}

void objdump32(file_mapped_t *file)
{
    Elf32_Ehdr *ehdr = (Elf32_Ehdr *) (file->load_addr);
    Elf32_Shdr *shdr = get_section_header_32(file, ehdr);
    char *sec_strtab = get_sec_strtab_32(file, shdr, ehdr);
    char *sec_name;

    print_obj_header32(file);
    for (int i = 0; i < ehdr->e_shnum; i++) {
        sec_name = sec_strtab + shdr[i].sh_name;
        if (!is_sec_valid32(&shdr[i], sec_name))
            continue;
        printf("Contents of section %s:\n", sec_name);
        print_section_content32(&shdr[i], file);
    }
}

int launch_objdump(file_mapped_t *file)
{
	int ret = is_32_bit(file, file->load_addr);

	if (ret == 1) {
		if (verify_hdr_32(file, file->load_addr))
			return (1);
		objdump32(file);
	} else if (ret == 0) {
		if (verify_hdr_64(file, file->load_addr))
			return (1);
		objdump64(file);
	} else {
		return (1);
	}
	return (0);
}

int handle_archive_objdump(file_mapped_t *file)
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
	printf("In archive %s:\n", file->file_name);
	fflush(NULL);
	for (; ahdr != NULL; ahdr = get_next_file(ahdr, &strtab, file)) {
		if (is_ar_file_mal_formated(ahdr))
			throw_malformated_archive(file);
		new_obj = create_mapped_file_from_archive(ahdr, strtab);
		(void) new_obj;
		if (!launch_objdump(new_obj))
			destroy_file_mapped(new_obj);
	}
	return (0);
}

int do_objdump(char *file_name)
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
		if (handle_archive_objdump(file))
			return (1);
		else {
			destroy_file_mapped(file);
			return (0);
		}
	} else if (!is_elf_file(file) || launch_objdump(file))
		return (1);
	destroy_file_mapped(file);
	return (0);
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