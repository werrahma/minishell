# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: werrahma <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/02 22:25:18 by werrahma          #+#    #+#              #
#    Updated: 2023/02/22 17:44:11 by werrahma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRC = \
	pipex.c 	\
	check_access.c 		\
	final_path.c 	\
	children.c 		\
	ft_split.c 	\
	ft_strdup.c \
	ft_strjoin.c \
	ft_strncmp.c ft_substr.c ft_strlen.c

SRC_BONUS = pipex_bonus/pipex.c 	\
	pipex_bonus/check_access.c 		\
	pipex_bonus/final_path.c 	\
	pipex_bonus/children.c 		\
	pipex_bonus/ft_split.c 	\
	pipex_bonus/ft_strdup.c \
	pipex_bonus/ft_strjoin.c \
	pipex_bonus/ft_strncmp.c\
	pipex_bonus/ft_substr.c\
	pipex_bonus/ft_strlen.c\
	pipex_bonus/here_doc.c \
	pipex_bonus/get_next_line.c\
	pipex_bonus/ft_strcmp.c \
	pipex_bonus/part_here_doc.c pipex_bonus/strcpm1.c pipex_bonus/help.c pipex_bonus/here_doc_help.c \
	pipex_bonus/ft_fail.c pipex_bonus/size_limiter.c pipex_bonus/get_strjoin.c

NAME = pipex
BONUS_NAME = pipex_bonus

OBJ = $(SRC:.c=.o)

OBJ_BONUS = $(SRC_BONUS:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

all: $(NAME)

bonus: $(BONUS_NAME)

$(BONUS_NAME) : $(OBJ_BONUS)
	$(CC) $(CFLAGS) $(OBJ_BONUS) -o $(NAME)
clean:
	rm -rf $(OBJ) $(OBJ_BONUS)
	
fclean: clean
	rm -rf $(NAME)
	
re: fclean all