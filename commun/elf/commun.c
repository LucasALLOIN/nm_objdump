/*
** EPITECH PROJECT, 2018
** Project nmobjdump
** File description:
** file.
*/

#include "file_utils.h"
#include "errors.h"
#include "my_elf.h"

int is_elf_file(file_mapped_t *file)
{
	char *pt = file->load_addr;

	if (file->size < 2) {
		throw_file_truncated(file);
		return (0);
	}
	(void) file;
	if ((pt[0] == 'M' && pt[1] == 'Z') || (pt[0] == 'Z' && pt[1] == 'M')) {
			return (1);
	}
	if (file->size < 4 || file->size < sizeof(Elf32_Ehdr)) {
		throw_file_not_recognized(file);
		return (0);
	}
	(void) file;
	if (pt[0] != 0x7f || pt[1] != 'E' || pt[2] != 'L' || pt[3] != 'F') {
		throw_file_not_recognized(file);
		return (0);
	}
	return (1);
}

int is_32_bit(file_mapped_t *file, Elf32_Ehdr *hdr)
{
	if (hdr->e_ident[EI_CLASS] == ELFCLASS32)
		return (1);
	else if (hdr->e_ident[EI_CLASS] == ELFCLASS64)
		return (0);
	else
		throw_file_not_recognized(file);
	return (42);
}

