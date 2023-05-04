SRC = \
		main.c

NAME = minishell

OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS = #-Wall -Wextra -Werror #-fsanitize=address -g

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ)
	
fclean: clean
	rm -rf $(NAME)
	
re: fclean all