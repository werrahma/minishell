
NAME = Minishell

CC = cc
#CFLAGS = -fsanitize=address -g

SRC = lexer.c lexer_utils.c main.c last_list.c

OBG = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBG)
	$(CC) $(CFLAGS) -o $(NAME) $(OBG) -ledit

clean :
	rm -rf	$(OBG)

fclean : clean
	rm -rf $(NAME)

re : fclean all