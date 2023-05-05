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

void	create_list(t_env **list, char **env);
void	ft_lstadd_back(t_env **lst, t_env *new);
t_env	*ft_lstnew(int content);

#endif