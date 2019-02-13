##
## EPITECH PROJECT, 2018
## Project nm
## File description:
## Build nm binary.
##

SRC	=	source/main.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-Werror -Wextra -W -Wall -Wparentheses -Wsign-compare -Wpointer-sign -Wuninitialized -Wunused-but-set-variable -I ./include/

NAME	=	my_nm

CC	=	gcc

all:	$(NAME)

$(NAME):	$(OBJ)
		$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

docker:
        sudo docker run -it -v `pwd`:/home/epitest -w /home/epitest epitechcontent/epitest-docker /bin/bash

re: fclean all
