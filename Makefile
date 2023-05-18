SRC = \
		main.c execution/minishell.c execution/ft_lstadd_back.c execution/ft_lstadd_front.c execution/ft_lstlast.c execution/ft_lstnew.c execution/create_list.c\
		execution/ft_strcmp.c execution/builtins.c execution/unset.c execution/exit.c execution/export.c\
		execution/cmp_env.c execution/sort_list.c\
		parsing/lexer.c parsing/lexer_utils.c parsing/last_list.c parsing/here_doc.c \
		get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c \
		pipex_bonus/check_access.c\
		pipex_bonus/children.c\
		pipex_bonus/final_path.c\
		pipex_bonus/ft_fail.c\
		pipex_bonus/multiple_pipe.c\
		pipex_bonus/pipex.c\
		pipex_bonus/size_limiter.c\

NAME = minishell
LIBFT = execution/libft/libft.a

OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS = #-fsanitize=address -g

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