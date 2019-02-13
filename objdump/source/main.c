/*
** EPITECH PROJECT, 2018
** Project objdump
** File description:
** Main file.
*/

#include "file_utils.h"
#include "my_elf.h"
#include "archive.h"
#include "errors.h"
#include "objdump.h"

int launch_objdump(file_mapped_t *file)
{
	int ret = is_32_bit(file, file->load_addr);

	if (ret == 1) {
		if (verify_hdr_32(file, file->load_addr))
			return (1);
		printf("\n%s:", file->file_name);
		fflush(NULL);
		printf("32bits !\n");
	} else if (ret == 0) {
		if (verify_hdr_64(file, file->load_addr))
			return (1);
		printf("\n%s:", file->file_name);
		fflush(NULL);
		printf("64bits !\n");
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
	printf("\n%s:", file->file_name);
	fflush(NULL);
	for (; ahdr != NULL; ahdr = get_next_file(ahdr, &strtab, file)) {
		if (is_ar_file_mal_formated(ahdr))
			throw_malformated_archive(file);
		new_obj = create_mapped_file_from_archive(ahdr, strtab);
		(void) new_obj;
		/*if (!launch_nm(new_obj, 42))
			destroy_file_mapped(new_obj);*/
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
		printf("Archive !\n");
		return (0);/*
		if (handle_archive_nm(file, argc))
			return (1);
		else {
			destroy_file_mapped(file);
			return (0);
		}*/
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