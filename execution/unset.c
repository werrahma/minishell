/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 21:15:35 by werrahma          #+#    #+#             */
/*   Updated: 2023/06/12 18:33:02 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(t_env **env, char **remove)
{
	t_env	*curent;
	t_env	*nxt;
	t_env	*tmp;
	t_env	*tmp1 = NULL;
	int		i;
	int		flag;

	curent = *env;
	tmp = *env;
	flag = 0;
	i = 1;
	int flag2 = 0;
	tmp1 = *env;
	while(remove[i])
	{
		while(*env && (*env)->next)
		{
			curent = *env;
			nxt = (*env)->next;
			if (!ft_strcmp(curent->key, remove[i]))
			{
				*env = (*env)->next;
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
		if (!(*env)->next && !ft_strcmp((*env)->key, remove[i]))
			flag2  =1 ;
		if (flag == 1)
		{
			flag = 0;
			tmp = tmp ->next;
		}
		*env = tmp;
		i++;
	}
	// printf("tmp.key === %s\n", (*env)->key);
	if (flag2 == 1)
	{
		free((*env)->key);
		free((*env)->value);
		(*env)->key = NULL;
		(*env)->value = NULL;
		free(*env);
		*env = NULL;
		// *env = tmp1;
	}
	else
		*env = tmp;
	// else
	// 	env = &tmp1;
	// while(*env)
	// {
	// 	printf("%s\n", (*env)->key);
	// 	*env = (*env)->next;
	// }
	// exit (1);
}