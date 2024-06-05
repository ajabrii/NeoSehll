CC = cc
NAME = minishell

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3
#------------------
SRC = MAIN/main.c
SRC += LEXICAL/lexical.c
SRC += BUILTINS/env.c BUILTINS/exit.c
SRC += UTILS/split.c UTILS/ft_strcnmp.c UTILS/substr.c UTILS/utilss.c UTILS/tools.c
SRC += UTILS/ft_strcpy.c UTILS/list_tools.c
#------------------

OBJ = $(SRC:.c=.o)
B_OBJ = $(B_SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -lreadline
clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: clean
.SECONDARY: $(OBJ)