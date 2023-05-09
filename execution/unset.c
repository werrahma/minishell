/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 21:15:35 by werrahma          #+#    #+#             */
/*   Updated: 2023/05/09 12:30:10 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(t_env **env, char **remove)
{
	t_env	*curent;
	t_env	*nxt;
	t_env	*tmp;
	int		i;
	int		flag;

	curent = *env;
	tmp = *env;
	flag = 0;
	i = 2;
	while(remove[i])
	{
		if (flag == 1)
		{
			flag = 0;
			tmp = tmp ->next;
		}
		*env = tmp;
		while(*env && (*env)->next)
		{
			curent = *env;
			nxt = (*env)->next;
			if (!ft_strcmp(curent->key, remove[i]))
			{
				*env = curent->next;
				flag = 1;
				break;
			}
			else if (!ft_strcmp(nxt->key, remove[i]))
			{
				curent->next = nxt->next;
				break ;
			}
			*env = (*env)->next;
		}
		i++;
	}
	*env = tmp;
	// while(*env)
	// {
	// 	printf("%s\n", (*env)->key);
	// 	*env = (*env)->next;
	// }
	// exit (1);
}