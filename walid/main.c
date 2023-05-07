/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:22:26 by werrahma          #+#    #+#             */
/*   Updated: 2023/05/07 15:35:54 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_agr(char **av, t_env *env)
{
	int	i;

	i = 0;
	while(av[i])
	{
		if (ft_strcmp("pwd", av[i]) == 0)
			pwd();
		else if (ft_strcmp("env", av[i]) == 0)
			ft_env(env);
		else if (ft_strcmp("echo", av[i]) == 0)
			echo(av);
		else if (ft_strcmp("cd", av[i]) == 0)
			ft_cd(env, av[i + 1]);
		// else if (ft_strcmp("exit", av[i]) == 0)
		// 	ft_exit(av[i + 1]);
		i++;
	}
	return (0);
}

int main(int ac, char **av, char **env)
{
    int i = 0;
    int j;
    char **hold;
    t_env   *list = NULL;
    t_env   *tmp = NULL;

	create_list(&list, env);
	tmp = list;
    while(env[i])
    {
		j = 0;
		hold = ft_split(env[i], '=');
		while (j < 2)
		{
		    list->key = hold[j];
		    j++;
			list->value = hold[j];
			j++;
		}
		list = list->next;
		i++;
    }
	list = tmp;
	// char *read;
	// while(1)
	// {
		// read = readline("minishell");
	check_agr(av, list);
	// }
	// i = 0;
	// while (tmp)
	// {
	// 	// printf("%d\n", i);
	// 	// i++;
	// 	printf("key == %s   value == %s\n", tmp->key, tmp->value);
	// 	tmp = tmp->next;
	// }

}