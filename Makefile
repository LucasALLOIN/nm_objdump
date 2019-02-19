##
## EPITECH PROJECT, 2018
## Project nm
## File description:
## Build nm binary.
##

COMMUN_DIR	=	commun

COMMUN_SRC = 	$(COMMUN_DIR)/elf/elf32.c \
				$(COMMUN_DIR)/elf/elf64.c \
				$(COMMUN_DIR)/elf/commun.c \
				$(COMMUN_DIR)/errors/throw.c \
				$(COMMUN_DIR)/file/utils.c \
				$(COMMUN_DIR)/my_malloc.c \
				$(COMMUN_DIR)/archive/ar.c

OBJDUMP_DIR	=	objdump

OBJDUMP_SRC	:=	$(OBJDUMP_DIR)/source/main.c

OBJDUMP_SRC +=	$(COMMUN_SRC)

OBJDUMP_OBJ	=	$(OBJDUMP_SRC:.c=.o)

NM_DIR	=	nm

NM_SRC	:=	$(NM_DIR)/source/main.c

NM_SRC +=	$(COMMUN_SRC)

NM_OBJ	=	$(NM_SRC:.c=.o)

CFLAGS	=	-Werror -Wextra -W -Wall -Wparentheses -Wpointer-sign -Wuninitialized -Wunused-but-set-variable -lm -I ./include -g

NM	=	my_nm

OBJDUMP	=	my_objdump

NM_RULE	=	nm

OBJDUMP_RULE	=	objdump

CC	=	gcc

all:	$(NM_RULE) $(OBJDUMP_RULE)

$(NM_RULE):	$(NM_OBJ)
		$(CC) -o $(NM) $(NM_OBJ) $(CFLAGS)

$(OBJDUMP_RULE):	$(OBJDUMP_OBJ)
		$(CC) -o $(OBJDUMP) $(OBJDUMP_OBJ) $(CFLAGS)

clean:
	rm -f $(OBJDUMP_OBJ)
	rm -f $(NM_OBJ)

fclean: clean
	rm -f $(NM)
	rm -f $(OBJDUMP)

docker:
	docker run -it -v `pwd`:/home/epitest -w /home/epitest epitechcontent/epitest-docker /bin/bash

re: fclean all
