SRC = \
		main.c execution/minishell.c execution/ft_lstadd_back.c execution/ft_lstadd_front.c execution/ft_lstlast.c execution/ft_lstnew.c execution/create_list.c\
		execution/ft_strcmp.c execution/builtins.c execution/unset.c execution/exit.c execution/export.c\
		execution/cmp_env.c execution/sort_list.c\
		parsing/lexer.c parsing/lexer_utils.c parsing/last_list.c parsing/here_doc.c  parsing/expand.c\
		get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c \
		execution/check_access.c\
		execution/children.c\
		execution/final_path.c\
		execution/ft_fail.c\
		execution/multiple_pipe.c\
		execution/pipex.c\
		execution/size_limiter.c\
		execution/ft_lstsize.c

NAME = minishell
LIBFT = execution/libft/libft.a

OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS = #-fsanitize=address -g3

all: $(NAME)

$(NAME): $(OBJ)
	cd execution/libft && $(MAKE)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) -lreadline

clean:
	rm -rf $(OBJ)
	rm -rf execution/libft/*.o
	
fclean: clean
	rm -rf $(NAME)
	rm -rf execution/libft/*.a
	
re: fclean all