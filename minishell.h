#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_list
{
	char **str;
}				t_list;

typedef struct s_env
{
	char	*key;
	char	*value;
	int		data;
	struct s_env  *next;
}				t_env;

#include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

#endif