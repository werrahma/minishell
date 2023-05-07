/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:18:00 by werrahma          #+#    #+#             */
/*   Updated: 2023/05/07 16:25:41 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_echo(char *s)
{
	int	i;

	i = 1;
	while (i < ft_strlen(s))
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}
void	print_cho(char **s, int i, int check)
{
	int	j;

	j = 0;
	if (check_echo(s[i]))
		j = 1;
	while (s[i])
	{
		if (j == 1)
		{
			if(!check_echo(s[i]))
				printf("%s", s[i]);
		}
		else
			printf("%s", s[i]);
		i++;
		if ((s[i] && !check_echo(s[i - 1])) || j == 0)
			printf(" ");
	}
	if (check == 0)
		printf("\n");
}


void	pwd(void)
{
    char	str[PATH_MAX];

	printf("%s\n", getcwd(str, PATH_MAX));
}
void	ft_env(t_env *env)
{
	int	i;

	i = 0;
	while(env)
	{
		if (env->value)
		{
			printf("%s", env->key);
			printf("=");
			printf("%s\n", env->value);
		}
		env = env->next;
	}
}
int	echo(char **str)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	// while(str[i])
	// {
		if (str[2][0] == '-')
		{
			if(!check_echo(str[i + 1]))
				return (print_cho(str, i + 1, 0), 0);
			else
				return (print_cho(str, i + 2, 1), 0);
		}
		else
			return (print_cho(str, i + 1, 0), 0);
	// 	i++;
	// }
	return (0);
	
}

void	ft_cd(t_env *env, char *fille)
{
	char	str[PATH_MAX];
	char	*path;
	char	*oldpwd;
	t_env	*tmp;
	static int	check;

	tmp = env;
	if (check == 0)
	{
		ft_lstadd_back(&env, ft_lstnew(1));
		env = ft_lstlast(env);
		env->key = "OLDPWD";
	}
	env = tmp;
	oldpwd = ft_strdup(getcwd(str, PATH_MAX));
	path = ft_strjoin("./", fille);
	chdir(path);
	printf("---%s\n", oldpwd);
	while(env)
	{
		if (ft_strcmp(env->key, "PWD"))
		{
			env->value = getcwd(str, PATH_MAX);
			printf("new pwd == %s\n", getcwd(str, PATH_MAX));
			check = 1;
		}
		else if (ft_strcmp(env->key, "OLDPWD"))
		{
			printf("oldpwd == %s\n", getcwd(str, PATH_MAX));
			env->value = oldpwd;
		}
		env = env->next;
	}
		// printf("%s\n", )
}

// void	ft_exit(char **av)
// {
// 	int	i;

// 	i = 1;
// 	exit (printf("",ft_atoi(av[i]));
// }
