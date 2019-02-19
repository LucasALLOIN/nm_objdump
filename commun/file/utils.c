/*
** EPITECH PROJECT, 2018
** Project nmobjdump
** File description:
** file.
*/

#include "file_utils.h"
#include "errors.h"
#include "string.h"

file_mapped_t *load_file_in_memory(char *file_name)
{
	int file_fd = open(file_name, O_RDONLY);
	file_mapped_t *file = NULL;
	struct stat buf;

	if (file_fd == -1 || fstat(file_fd, &buf) == -1 || buf.st_size == 0)
		return (NULL);
	else if (!S_ISREG(buf.st_mode)) {
		fprintf(stderr, "%s: Warning: '%s' is a directory\n",
			program_invocation_name, file_name);
		return (NULL);
	}
	file = my_malloc(sizeof(file_mapped_t));
	file->load_addr = mmap(NULL, buf.st_size, PROT_READ, MAP_PRIVATE, \
	file_fd, 0);
	file->size = buf.st_size;
	file->file_name = strdup(file_name);
	file->is_ar = 0;
	close(file_fd);
	return (file);
}

void destroy_file_mapped(file_mapped_t *file)
{
	if (!file->is_ar)
		munmap(file->load_addr, file->size);
	free(file->file_name);
	free(file);
}