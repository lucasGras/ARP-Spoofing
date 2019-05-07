##
## EPITECH PROJECT, 2018
## lib malloc
## File description:
## Makefile
##

SRC		=		src/main.c \
				src/parser/parser.c \

OBJ		=		$(SRC:.c=.o)

CFLAGS	+=		-I./include

NAME	=	myARPspoof

all:	$(NAME)

$(NAME):	$(OBJ)
		gcc $(OBJ) -o $(NAME) -lcrypto

clean:
	find -name '*.o' -delete
	rm -f mychap

fclean:	clean
	find -name '*.gc*' -delete
	find -name 'vgcore.*' -delete

purge_build:
	rm -rf build/*

re:	fclean all
