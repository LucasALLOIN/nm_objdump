cmake_minimum_required(VERSION 3.9)

set(CMAKE_C_STANDARD 99)
set(SOURCE_DIR_NM nm/source)
set(SOURCE_DIR_OBJDUMP objdump/source)
set(PROJECT_NAME nmobjdump)
set(EXECUTABLE_NAME_NM my_nm)
set(EXECUTABLE_NAME_OBJDUMP my_objdump)

project(${PROJECT_NAME})
include_directories(include)

add_executable(${EXECUTABLE_NAME_NM}    ${SOURCE_DIR_NM}/main.c commun/elf/elf32.c commun/elf/elf64.c include/my_elf.h include/file_utils.h commun/file/utils.c include/errors.h commun/my_malloc.c include/my_malloc.h commun/errors/throw.c commun/archive/ar.c commun/elf/commun.c)
add_executable(${EXECUTABLE_NAME_OBJDUMP}   ${SOURCE_DIR_OBJDUMP}/main.c commun/elf/elf32.c commun/elf/elf64.c include/file_utils.h commun/file/utils.c commun/my_malloc.c commun/errors/throw.c commun/archive/ar.c)