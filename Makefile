SRC = \
		execution/main.c execution/ft_lstadd_back.c execution/ft_lstadd_front.c execution/ft_lstlast.c execution/ft_lstnew.c execution/create_list.c\
		execution/ft_strcmp.c execution/builtins.c execution/unset.c execution/exit.c execution/export.c\
		execution/cmp_env.c execution/sort_list.c\
		parsing/lexer.c parsing/lexer_utils.c parsing/last_list.c parsing/here_doc.c \
		get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c \

NAME = minishell
LIBFT = execution/libft/libft.a

OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS = #-fsanitize=address -g

all: $(NAME)

$(NAME): $(OBJ)
	cd execution/libft && $(MAKE)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) -ledit

clean:
	rm -rf $(OBJ)
	rm -rf libft/*.o
	
fclean: clean
	rm -rf $(NAME)
	rm -rf libft/*.a
	
re: fclean all