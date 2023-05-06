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
// void	ft_cd(t_env *env);
int		ft_strcmp(const char *s1, const char *s2);
void	pwd(void);
void	ft_env(t_env *env);
int		echo(char **str);
void	ft_cd(char *fille);

#endif