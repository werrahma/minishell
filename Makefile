SRC = \
		main.c\
		parsing/lexer.c parsing/last_list.c\
		parsing/here_doc.c parsing/expand.c parsing/stxe.c\
		parsing/utils/lexer_utils.c \
		parsing/utils/lexer_define.c \
		parsing/utils/list_utils.c \
		execution/minishell.c execution/ft_lstadd_back.c execution/ft_lstadd_front.c execution/ft_lstlast.c execution/ft_lstnew.c execution/create_list.c\
		execution/ft_strcmp.c execution/builtins.c execution/our_unset.c execution/exit.c execution/export.c\
		execution/sort_list.c\
		execution/check_access.c\
		execution/children.c\
		execution/final_path.c\
		execution/multiple_pipe.c\
		execution/pipes_monitor.c\
		execution/size_limiter.c execution/help_export.c execution/help2_export.c\
		execution/ft_lstsize.c execution/get_env.c execution/split_env.c execution/our_echo.c

NAME = minishell
LIBFT = execution/libft/libft.a

READLINE = -lreadline -L /Users/yahamdan/.brew/Cellar/readline/8.2.1/lib -I /Users/yahamdan/.brew/Cellar/readline/8.2.1/include

OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS = #-fsanitize=address -g #-Wall -Wextra -Werror 

all: $(NAME)

$(NAME): $(OBJ)
	cd execution/libft && $(MAKE)
	$(CC) $(CFLAGS) $(READLINE) $(OBJ) $(LIBFT) -o $(NAME) 

clean:
	rm -rf $(OBJ)
	rm -rf execution/libft/*.o
	
fclean: clean
	rm -rf $(NAME)
	rm -rf execution/libft/*.a
	
re: fclean all