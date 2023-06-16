/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:22:26 by werrahma          #+#    #+#             */
/*   Updated: 2023/06/16 19:16:56 by werrahma         ###   ########.fr       */
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
	if (!ft_strcmp("pwd", cmd[0]) || !ft_strcmp("env", cmd[0]) || !ft_strcmp("cd", cmd[0]) || !ft_strcmp("unset", cmd[0]) || !ft_strcmp("exit", cmd[0])
	|| !ft_strcmp("export", cmd[0]) || !ft_strcmp("echo", cmd[0]))
		return (1);
	return (0);
}


void	fill_list(t_env **list, char **env)
{
	int	i;
	int	j;
	char **hold;
	t_env	*tmp = NULL;

	i = 0;

	// create_list(&list, env);
	tmp = *list;
	while(env[i])
	{
		j = 0;
		// hold = ft_split(env[i], '=');
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

int	check_arg(char **av, t_env **env)
{
	int	i;
	int	hold;

	i = 0;
	// while((*env))
	// {
	// 	printf("%s\n", (*env)->key);
	// 	(*env) = (*env)->next;
	// }
	// exit(1);
	// while(av[i])
	// 	printf("%s\n", av[i++]);
	// exit(1);
	// while(av[i])
	// {
		if (ft_strcmp("pwd", av[i]) == 0)
			pwd();
		else if (ft_strcmp("env", av[i]) == 0)
			print_env(*env);
		else if (ft_strcmp("echo", av[i]) == 0)
		{
			echo(av);
		}
		else if (ft_strcmp("cd", av[i]) == 0)
		{
			if (!av[i + 1])
				our_cd(*env, av[i]);
			else
				our_cd(*env, av[i + 1]);
		}
		else if (!ft_strcmp("unset", av[i]))
		{
			unset(env, av);
		}
		else if (ft_strcmp("exit", av[i]) == 0)
		{
			hold = my_exit(av);
			if(hold != -1)
				exit(hold);
		}
		else if (!ft_strcmp("export", av[i]))
		{
			our_export(env, av);
			// sort_list(env);
			// exit(1);
		}
		// else
		// {
		// 	pipe(pipes->fd[0]);
		// 	pipe(pipes->fd[1]);
		// 	pipes_monitor(list, pipes->env, pipes);
		// }
	// 	i++;
	// }
	// exit(1);
	// while(1);
	// int x = 0;
	// while(av[x])
	// 	free(av[x++]);
	// free(av);
	// system("leaks minishell");
	return (0);
}

// int main(int ac, char **av, char **env)
// {
//     int i = 0;
//     int j;
//     char **hold;
//     t_env   *list = NULL;
//     // t_env   *tmp = NULL;

// 	create_list(&list, env);
// 	fill_list(&list, env);
// 	// tmp = list;
//     // while(env[i])
//     // {
// 	// 	j = 0;
// 	// 	hold = ft_split(env[i], '=');
// 	// 	while (j < 2)
// 	// 	{
// 	// 		list->key = hold[j];
// 	// 		j++;
// 	// 		list->value = hold[j];
// 	// 		j++;
// 	// 	}
// 	// 	list = list->next;
// 	// 	i++;
// 	// }
// 	// list = tmp;
// 	// char *read;
// 	// while(1)
// 	// {
// 		// read = readline("minishell");
// 	// while(list)
// 	// {
// 	// 	printf("%s\n", list->key);
// 	// 	list = list->next;
// 	// }
// 	// exit(2);
// 	check_agr(av, &list);
// 	// printf("\n\n\n\n");
// 	while(list)
// 	{
// 		printf("%s == ", list->key);
// 		printf("%s\n", list->value);
// 		list = list->next;
// 	}
// 	// }
// 	// i = 0;
// 	// while (tmp)
// 	// {
// 	// 	// printf("%d\n", i);
// 	// 	// i++;
// 	// 	printf("key == %s   value == %s\n", tmp->key, tmp->value);
// 	// 	tmp = tmp->next;
// 	// }

// }