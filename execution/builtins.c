/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <werrahma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:18:00 by werrahma          #+#    #+#             */
/*   Updated: 2023/05/29 21:47:30 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_echo(char *s)
{
	int	i;

	i = 1;
	if (s[0] == '-' && ft_strlen(s) == 1)
			return (0);
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
	int	flag;
	int	flag2;

	flag = 0;
	flag2 = 0;
	if (check_echo(s[i]))
		flag = 1;
	while (s[i])
	{
		if (flag == 1)
		{
			if(!check_echo(s[i]))
			{
				flag = 0;
				printf("%s", s[i]);
			}
		}
		// if (flag2 == 1)
		// 	printf("%s", s[i]);
		else
			printf("%s", s[i]);
		i++;
		if (s[i] && !check_echo(s[i - 1]))
			printf(" ");
		// if ((s[i] || !check_echo(s[i - 1])))
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

	i = 0;
	j = 0;
	if (str_len(str) <= 1)
		exit(1);
	// while(str[i])
	// {
		if (str[1][0] == '-')
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

int	check_oldpwd(t_env *env, int *flag)
{
	while (env)
	{
		if (ft_strcmp(env->key, "OLDPWD") == 0)
			return (1);
		if (!ft_strcmp(env->key, "HOME"))
			*flag = 1;
		env = env->next;
	}
	return (0);
}

void	ft_cd(t_env *env, char *file)
{
	char	str[PATH_MAX];
	char	*path;
	char	*oldpwd;
	t_env	*tmp;
	int		flag;
	static int	check;

	tmp = env;
	flag = 0;
	if (check_oldpwd(env, &flag));
	else if (check == 0)
	{
		ft_lstadd_back(&env, ft_lstnew(1));
		env = ft_lstlast(env);
		env->key = "OLDPWD";
	}
	env = tmp;
	if (!ft_strcmp(file, "cd") && flag == 1)
		file = ft_strdup("/Users/werrahma");
	else if (!ft_strcmp(file, "cd") && flag == 0)
	{
		write(1, "minishell: cd:", 14);
		write(2, " HOME not set\n", 14);
		return ;
	}
	oldpwd = getcwd(NULL, 0);
	if (chdir(file) == -1)
	{
		write(1, "minishell: cd:", 14);
		write(1, file, ft_strlen(file));
		write(2, ": No such file or directory\n", 28);
	}
	while(env)
	{
		if (ft_strcmp(env->key, "PWD") == 0)
		{
			env->value = getcwd(NULL, 0);
			// printf("new pwd == %s\n", env->value);
			check = 1;
		}
		else if (ft_strcmp(env->key, "OLDPWD") == 0)
		{
			env->value = oldpwd;
			// free(oldpwd);
			// printf("oldpwd == %s\n", oldpwd);
		}
		env = env->next;
	}
}

// void	ft_exit(char **av)
// {
// 	int	i;

// 	i = 1;
// 	exit (printf("",ft_atoi(av[i]));
// }
