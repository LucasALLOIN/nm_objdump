/*
** EPITECH PROJECT, 2018
** Project nmobjdump
** File description:
** file.
*/

#include "file_utils.h"
#include "my_elf.h"
#include "errors.h"

char *get_sec_strtab_32(file_mapped_t *f, Elf32_Shdr *sh, Elf32_Ehdr *ehdr)
{
	return (f->load_addr + sh[ehdr->e_shstrndx].sh_offset);
}

Elf32_Shdr *get_section_header_32(file_mapped_t *file, Elf32_Ehdr *hdr)
{
	return (file->load_addr + hdr->e_shoff);
}

int verify_e_shoff_shnum_32(file_mapped_t *file, Elf32_Ehdr *hdr)
{
	Elf32_Off tables_size = hdr->e_shentsize * hdr->e_shnum;
	Elf32_Off end_table_off = tables_size + hdr->e_shoff;
	Elf32_Shdr *shdr = file->load_addr + hdr->e_shoff;

	if (end_table_off < file->size) {
		throw_file_not_recognized(file);
		return (1);
	} else if (end_table_off > file->size) {
		throw_file_truncated(file);
		return (1);
	}
	for (uint32_t i = 0; i < hdr->e_shnum; i++) {
		if (shdr[i].sh_type != SHT_NULL && \
		shdr[i].sh_link > hdr->e_shnum) {
			throw_file_not_recognized(file);
			return (1);
		}
	}
	return (0);
}

int verify_hdr_32(file_mapped_t *file, Elf32_Ehdr *hdr)
{
	if (hdr->e_ident[EI_DATA] != ELFDATA2LSB && hdr->e_ident[EI_DATA] != \
	ELFDATA2MSB) {
		throw_file_not_recognized(file);
		return (1);
	} else if (hdr->e_ident[EI_VERSION] != EV_CURRENT) {
		throw_file_not_recognized(file);
		return (1);
	}
	return (verify_e_shoff_shnum_32(file, hdr));
}