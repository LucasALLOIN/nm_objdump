/*
** EPITECH PROJECT, 2018
** Project nmobjdump
** File description:
** file.
*/

#ifndef NMOBJDUMP_FILE_UTILS_H
#define NMOBJDUMP_FILE_UTILS_H

#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include "my_malloc.h"

typedef struct file_mapped_s {
	void *load_addr;
	char *file_name;
	unsigned int size;
	int is_ar;
} file_mapped_t;

file_mapped_t *load_file_in_memory(char *file_name);
void destroy_file_mapped(file_mapped_t *file);

#endif //NMOBJDUMP_FILE_UTILS_H
