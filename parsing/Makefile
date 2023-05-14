
NAME = Minishell
LIBFT = ../execution/libft/libft.a

CC = cc
# CFLAGS = -fsanitize=address -g

SRC = lexer.c lexer_utils.c main.c last_list.c here_doc.c \
		../get_next_line/get_next_line.c \
		../get_next_line/get_next_line_utils.c \

OBG = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBG)
	cd ../execution/libft && $(MAKE)
	$(CC) $(CFLAGS) -o $(NAME) $(OBG) $(LIBFT) -ledit

clean :
	rm -rf	$(OBG)
	rm -rf libft/*.o

fclean : clean
	rm -rf $(NAME)
	rm -rf libft/*.a

re : fclean all