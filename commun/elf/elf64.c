/*
** EPITECH PROJECT, 2018
** Project nmobjdump
** File description:
** file.
*/

#include "file_utils.h"
#include "my_elf.h"
#include "errors.h"

char *get_sec_strtab_64(file_mapped_t *f, Elf64_Shdr *sh, Elf64_Ehdr *ehdr)
{
	return (f->load_addr + sh[ehdr->e_shstrndx].sh_offset);
}

Elf64_Shdr *get_section_header_64(file_mapped_t *file, Elf64_Ehdr *hdr)
{
	return (file->load_addr + hdr->e_shoff);
}

int verify_hdr_64(file_mapped_t *file, Elf64_Ehdr *hdr)
{
	if (file->size < sizeof(Elf64_Ehdr)) {
		throw_file_not_recognized(file);
		return (1);
	}
	(void) file;
	if (hdr->e_ident[EI_DATA] != ELFDATA2LSB && hdr->e_ident[EI_DATA] != \
	ELFDATA2MSB) {
		throw_file_not_recognized(file);
		return (1);
	} else if (hdr->e_ident[EI_VERSION] != EV_CURRENT) {
		throw_file_not_recognized(file);
		return (1);
	}
	return (verify_e_shoff_shnum_64(file, hdr));
}

int verify_e_shoff_shnum_64(file_mapped_t *file, Elf64_Ehdr *hdr)
{
	Elf64_Off tables_size = hdr->e_shentsize * hdr->e_shnum;
	Elf64_Off end_table_off = tables_size + hdr->e_shoff;
	Elf64_Shdr *shdr = file->load_addr + hdr->e_shoff;

	if (end_table_off < file->size) {
		throw_file_not_recognized(file);
		return (1);
	} else if (end_table_off > file->size) {
		throw_file_truncated(file);
		return (1);
	}
	for (uint64_t i = 0; i < hdr->e_shnum; i++) {
		if (shdr[i].sh_type != SHT_NULL && \
		shdr[i].sh_link > hdr->e_shnum) {
			throw_file_not_recognized(file);
			return (1);
		}
	}
	return (0);
}