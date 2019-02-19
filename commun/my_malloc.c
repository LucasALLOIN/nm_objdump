/*
** EPITECH PROJECT, 2018
** Project nmobjdump
** File description:
** file.
*/

#include "my_malloc.h"
#include "errors.h"
#include "string.h"

void *my_malloc(size_t size)
{
    void *ptr = malloc(size);

    if (ptr == NULL)
        exit(MY_EXIT_FAILURE);
    memset(ptr, 0, size);
    return (ptr);
}