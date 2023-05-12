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
#include <stdlib.h>

// #include <readline/readline.h>
// #include <readline/history.h>

void	create_list(t_env **list, char **env);
void	ft_lstadd_back(t_env **lst, t_env *new);
t_env	*ft_lstnew(int content);
t_env	*ft_lstlast(t_env *lst);
// void	ft_cd(t_env *env);
int		ft_strcmp(const char *s1, const char *s2);
void	pwd(void);
void	ft_env(t_env *env);
int		echo(char **str);
void	ft_cd(t_env *env, char *file);
void	unset(t_env **env, char **remove);
int		my_exit(char **av);
int		str_len(char **av);
void	my_export(t_env **env, char **av);
int		cmp_env(char *str1, char *str2);
void	sort_list(t_env **env);

#endif