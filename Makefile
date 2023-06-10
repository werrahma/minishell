SRC = \
		main.c\
		parsing/lexer.c parsing/lexer_utils.c parsing/last_list.c parsing/here_doc.c\
		parsing/expand.c parsing/stxe.c\
		get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c \
		execution/minishell.c execution/ft_lstadd_back.c execution/ft_lstadd_front.c execution/ft_lstlast.c execution/ft_lstnew.c execution/create_list.c\
		execution/ft_strcmp.c execution/builtins.c execution/unset.c execution/exit.c execution/export.c\
		execution/cmp_env.c execution/sort_list.c\
		execution/check_access.c\
		execution/children.c\
		execution/final_path.c\
		execution/ft_fail.c\
		execution/multiple_pipe.c\
		execution/pipes_monitor.c\
		execution/size_limiter.c\
		execution/ft_lstsize.c

NAME = minishell
LIBFT = execution/libft/libft.a

READLINE = -lreadline -L /Users/yahamdan/.brew/Cellar/readline/8.2.1/lib -I /Users/yahamdan/.brew/Cellar/readline/8.2.1/include

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