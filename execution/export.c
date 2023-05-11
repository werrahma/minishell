/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:07:11 by werrahma          #+#    #+#             */
/*   Updated: 2023/05/11 20:00:19 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_byequals(t_env *env, char *str)
{
	int	i;

	i = 0;
	// while(str[i] && str[i] != '=')
	// {
		env->key = ft_strdup(str - ft_strlen(str));
	// }
		printf("%s\n", env->key);
		exit(1);
	while(str[i])
	{
		env->value = ft_strdup(str + ft_strlen(str));
		i++;
	}
}

// void	export_arg(char *av)
// {	
// }

void	my_export(t_env **env, char **av)
{
	int	i;
	int	j;
    t_env *tmp;

	i = 2;
	j = 0;
	tmp = *env;
	// printf("%s\n", av[i]);
	// exit(1);
	while(av[i])
	{
		ft_lstadd_back(env, ft_lstnew(1));
		*env = ft_lstlast(*env);
		split_byequals(*env, av[i]);
		i++;
	}
	while (tmp)
	{
		printf("%s\n", tmp->key);
		tmp = tmp->next;
	}
}