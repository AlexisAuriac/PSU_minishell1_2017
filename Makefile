##
## EPITECH PROJECT, 2017
## minishell1
## File description:
## Makefile for minishell1
##

SRC	=	src/main.c		\
		src/prompt.c		\
		src/errors.c		\
		src/my_cd.c		\
		src/my_env.c		\
		src/my_setenv.c		\
		src/my_unsetenv.c	\
		src/my_exec.c		\
		src/utilities.c		\
		src/split_command.c

OBJ	=	$(SRC:.c=.o)

CPPFLAGS+=	-I include

CFLAGS	+=	-Wall -Wextra

LDFLAGS	=	-Llib -lmy

NAME	=	mysh

all	:	$(NAME)

$(NAME)	:	$(OBJ)
		$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean	:
		$(RM) -f $(OBJ)

fclean	:	clean
		$(RM) -f $(NAME)

re	:	fclean	all

.PHONY	:	all clean fclean re
