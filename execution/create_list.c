/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 12:08:24 by werrahma          #+#    #+#             */
/*   Updated: 2023/06/03 17:14:10 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_list(t_env **list, char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		ft_lstadd_back(list, ft_lstnew(i));
		i++;
	}
}

void	create_env(t_env **list)
{
	int	i;
	t_env *tmp;

	i = 0;
	while(i < 3)
		ft_lstadd_back(list, ft_lstnew(i++));
	i = 0;
	// while(*list)
	// {
	// 	printf("%d\n", (*list)->data);
	// 	*list = (*list)->next;
	// }
	tmp = *list;
	while(i < 3 && *list)
	{
		if (i == 0)
		{
			(*list)->key = ft_strdup("PWD");
			(*list)->value = ft_strdup("/Users/werrahma/Desktop/minishell_copy");
		}
		else if (i == 1)
		{
			(*list)->key = ft_strdup("SHLVL");
			(*list)->value = ft_strdup("1");
		}
		else if (i == 2)
		{
			(*list)->key = ft_strdup("_");
			(*list)->value = ft_strdup("/usr/bin/env");
		}
		*list = (*list)->next;
		i++;
	}
	*list = tmp;
}