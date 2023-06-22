/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahamdan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:18:00 by werrahma          #+#    #+#             */
/*   Updated: 2023/06/21 20:17:24 by yahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(void)
{
	char	str[PATH_MAX];

	printf("%s\n", getcwd(str, PATH_MAX));
	return (status_checker(0));
}

int	print_env(t_env *env)
{
	int	i;

	i = 0;
	if (!env)
	{
		write(2, "env: No such file or directory\n", 31);
		return (1);
	}
	while (env)
	{
		if (env->value)
		{
			printf("%s", env->key);
			printf("=");
			printf("%s\n", env->value);
		}
		env = env->next;
	}
	return (status_checker(0));
}

// int	check_oldpwd(t_env *env, int *flag)
// {
// 	while (env)
// 	{
// 		if (ft_strcmp(env->key, "OLDPWD") == 0)
// 			return (1);
// 		if (!ft_strcmp(env->key, "HOME"))
// 			*flag = 1;
// 		env = env->next;
// 	}
// 	return (0);
// }

// void	our_cd(t_env *env, char *file)
// {
// 	char		*oldpwd;
// 	t_env		*tmp;
// 	int			flag;
// 	static int	check;
// 	extern int	g_status;
// 	char		*pwd;
// 	int flag2 = 0;

// 	tmp = env;
// 	flag = 0;
// 	if (check_oldpwd(env, &flag))
// 		;
// 	else if (check == 0)
// 	{
// 		ft_lstadd_back(&env, ft_lstnew());
// 		env = ft_lstlast(env);
// 		env->key = ft_strdup("OLDPWD");
// 	}
// 	env = tmp;
// 	if (!ft_strcmp(file, "cd") && flag == 1)
// 	{
// 		flag2 = 1;
// 		file = ft_strdup("/Users/werrahma");
// 	}
// 	else if (!ft_strcmp(file, "cd") && flag == 0)
// 	{
// 		write(1, "minishell: cd:", 14);
// 		write(2, " HOME not set\n", 14);
// 		g_status = 1;
// 		return ;
// 	}
// 	oldpwd = getcwd(NULL, 0);
// 	if (chdir(file) == -1)
// 	{
// 		free(oldpwd);
// 		write(1, "minishell: cd:", 14);
// 		write(1, file, ft_strlen(file));
// 		write(2, ": No such file or directory\n", 28);
// 		g_status = 1;
// 		return ;
// 	}
// 	while (env)
// 	{
// 		if (!ft_strcmp(env->key, "PWD"))
// 		{
// 			free(env->value);
// 			pwd = getcwd(NULL, 0);
// 			env->value = ft_strdup(pwd);
// 			check = 1;
// 			free(pwd);
// 		}
// 		else if (!ft_strcmp(env->key, "OLDPWD"))
// 		{
// 			free(env->value);
// 			env->value = ft_strdup(oldpwd);
// 		}
// 		env = env->next;
// 	}
// 	if (flag2 == 1)
// 		free(file);
// 	free(oldpwd);
// }
