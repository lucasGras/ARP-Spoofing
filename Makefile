##
## EPITECH PROJECT, 2018
## lib malloc
## File description:
## Makefile
##

SRC		=		src/main.c \
				src/spoofing.c \
				src/parser/parser.c \
				src/arp/create.c \
				src/arp/delete.c \
				src/mac/retrieve_mac_addr.c \
				src/socket/create.c \
				src/socket/delete.c \
				src/parser/dump.c \
				src/parser/getnbr.c \

OBJ		=		$(SRC:.c=.o)

CFLAGS	+=		-I./include -g3

NAME	=	myARPspoof

all:	$(NAME)

$(NAME):	$(OBJ)
		gcc $(OBJ) -o $(NAME) -g3 -lm

clean:
	find -name '*.o' -delete
	rm -f myARPspoof

fclean:	clean
	find -name '*.gc*' -delete
	find -name 'vgcore.*' -delete

purge_build:
	rm -rf build/*

re:	fclean all
