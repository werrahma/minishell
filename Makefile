SRC = \
		main.c ft_lstadd_back.c ft_lstadd_front.c ft_lstlast.c ft_lstnew.c \

NAME = minishell
LIBFT = libft/libft.a

OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS = #-Wall -Wextra -Werror #-fsanitize=address -g

all: $(NAME)

$(NAME): $(OBJ)
	cd libft && $(MAKE)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

clean:
	rm -rf $(OBJ)
	rm -rf libft/*.o
	
fclean: clean
	rm -rf $(NAME)
	rm -rf libft/*.a
	
re: fclean all