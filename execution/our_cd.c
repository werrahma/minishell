/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 14:47:58 by werrahma          #+#    #+#             */
/*   Updated: 2023/06/21 16:23:06 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	add_oldpwd(t_env **env)
{
	ft_lstadd_back(env, ft_lstnew());
	*env = ft_lstlast(*env);
	(*env)->key = ft_strdup("OLDPWD");
}

int	cd_failure(char *oldpwd, char *file, int flag)
{
	if (flag == 1)
	{
		free(oldpwd);
		write(1, "minishell: cd:", 14);
		write(1, file, ft_strlen(file));
		write(2, ": No such file or directory\n", 28);
		return (1);
	}
	else
	{
		write(1, "minishell: cd:", 14);
		write(2, " HOME not set\n", 14);
	}
	return (1);
}

int	cd_monitor(t_env *env, char *pwd, char *oldpwd)
{
	int	check;

	check = 0;
	while (env)
	{
		if (!ft_strcmp(env->key, "PWD"))
		{
			free(env->value);
			pwd = getcwd(NULL, 0);
			env->value = ft_strdup(pwd);
			check = 1;
			free(pwd);
		}
		else if (!ft_strcmp(env->key, "OLDPWD"))
		{
			free(env->value);
			env->value = ft_strdup(oldpwd);
		}
		env = env->next;
	}
	return (check);
}

int	our_cd(t_env *env, char *file)
{
	t_var		var;
	static int	check;

	var.tmp = env;
	var.flag = 0;
	if (check_oldpwd(env, &var.flag))
		;
	else if (check == 0)
		add_oldpwd(&env);
	env = var.tmp;
	if (!ft_strcmp(file, "cd") && var.flag == 1)
	{
		var.flag2 = 1;
		file = ft_strdup("/Users/werrahma");
	}
	else if (!ft_strcmp(file, "cd") && var.flag == 0)
		return (status_checker(cd_failure(var.oldpwd, file, -1)));
	var.oldpwd = getcwd(NULL, 0);
	if (chdir(file) == -1)
		return (status_checker(cd_failure(var.oldpwd, file, 1)));
	check = cd_monitor(env, var.pwd, var.oldpwd);
	if (var.flag2 == 1)
		free(file);
	free(var.oldpwd);
	return (status_checker(0));
}
