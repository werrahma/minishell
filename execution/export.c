/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:07:11 by werrahma          #+#    #+#             */
/*   Updated: 2023/06/21 14:52:27 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_string_inlist(t_env *env, char *arg)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	if (arg[i] && !arg[i + 1])
		flag = 1;
	while (env)
	{
		if (!ft_strncmp(env->key, arg, ft_strlen(env->key)))
		{
			if (flag == 1)
			{
				free(env->key);
				env->key = ft_strdup(arg);
			}
			return (1);
		}
		env = env->next;
	}
	return (0);
}

void	print_export(t_env **env, t_env *c_env)
{
	t_env	*c_tmp;

	copy_env(env, &c_env);
	sort_list(&c_env);
	c_tmp = c_env;
	while ((c_env))
	{
		printf("declare -x ");
		printf("%s", (c_env)->key);
		if ((c_env)->value != NULL)
		{
			printf("=");
			printf("\"");
			printf("%s", (c_env)->value);
			printf("\"\n");
		}
		else
			printf("\n");
		(c_env) = (c_env)->next;
	}
	c_env = c_tmp;
	free_env(&c_env);
}

int	our_export(t_env **env, char **av)
{
	int			i;
	t_env		*tmp;
	t_env		*c_env;
	static int	cnst;

	i = 1;
	tmp = *env;
	c_env = NULL;
	if (!tmp)
		cnst = 0;
	if (str_len(av) == 1)
		print_export(env, c_env);
	else
	{
		while (av[i])
		{
			if (!export_monitor(env, &tmp, av[i], &cnst))
				return (*env = tmp, status_checker(1));
			i++;
		}
	}
	*env = tmp;
	return (status_checker(0));
}
