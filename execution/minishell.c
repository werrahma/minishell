/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:22:26 by werrahma          #+#    #+#             */
/*   Updated: 2023/06/17 20:33:17 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	out_free(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

int	have_builtins(char **cmd)
{
	if (!cmd[0])
		return (0);
	if (!ft_strcmp("pwd", cmd[0]) || !ft_strcmp("env", cmd[0])
		|| !ft_strcmp("cd", cmd[0]) || !ft_strcmp("unset", cmd[0])
		|| !ft_strcmp("exit", cmd[0]) || !ft_strcmp("export", cmd[0])
		|| !ft_strcmp("echo", cmd[0]))
		return (1);
	return (0);
}

void	fill_list(t_env **list, char **env)
{
	int		i;
	int		j;
	char	**hold;
	t_env	*tmp;

	i = 0;
	tmp = *list;
	while (env[i])
	{
		j = 0;
		hold = split_env (env[i]);
		while (j < 2)
		{
			(*list)->key = ft_strdup(hold[j]);
			j++;
			(*list)->value = ft_strdup(hold[j]);
			j++;
		}
		out_free(hold);
		(*list) = (*list)->next;
		i++;
	}
	(*list) = tmp;
}

void	check_arg(char **av, t_env **env)
{
	extern int	stx;

	if (!ft_strcmp("pwd", av[0]))
		pwd();
	else if (!ft_strcmp("env", av[0]))
		print_env(*env);
	else if (!ft_strcmp("echo", av[0]))
		our_echo(av);
	else if (!ft_strcmp("cd", av[0]))
	{
		if (!av[1])
			our_cd(*env, av[0]);
		else
			our_cd(*env, av[1]);
	}
	else if (!ft_strcmp("unset", av[0]))
		our_unset(env, av);
	else if (!ft_strcmp("exit", av[0]))
	{
		stx = my_exit(av);
		if (stx != -1)
			exit(stx);
	}
	else if (!ft_strcmp("export", av[0]))
		our_export(env, av);
}
