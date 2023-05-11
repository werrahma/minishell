/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:18:00 by werrahma          #+#    #+#             */
/*   Updated: 2023/05/11 15:36:39 by werrahma         ###   ########.fr       */
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
		if ((s[i] && !check_echo(s[i - 1])))
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
	if (str_len(str) <= 1)
		exit(1);
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

int	check_oldpwd(t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, "OLDPWD") == 0)
			return (1);
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
	static int	check;

	tmp = env;
	if (check_oldpwd(env));
	else if (check == 0)
	{
		ft_lstadd_back(&env, ft_lstnew(1));
		env = ft_lstlast(env);
		env->key = "OLDPWD";
	}
	env = tmp;
	oldpwd = getcwd(NULL, 0);
	// printf("%s\n", oldpwd);
	// while(1);
	chdir(file);
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
			free(oldpwd);
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