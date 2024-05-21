CC = cc
NAME = minishell

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3
#------------------
SRC = neoshell.c ft_exit.c Neotoken.c pipex_tools.c tools.c lexical.c
SRC += utils/split.c utils/ft_strcnmp.c utils/substr.c utils/utilss.c utils/tools.c
#------------------

OBJ = $(SRC:.c=.o)
B_OBJ = $(B_SRC:.c=.o)

all: $(NAME) clean

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -lreadline
clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean
.SECONDARY: $(OBJ)