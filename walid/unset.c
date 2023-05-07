/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <werrahma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 21:15:35 by werrahma          #+#    #+#             */
/*   Updated: 2023/05/07 23:19:59 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(t_env **env, char *remove)
{
	t_env	*curent;
	t_env	*nxt;
	t_env	*tmp;

	// curent = *env;
	tmp = *env;
	while(*env)
	{
		curent = *env;
		nxt = (*env)->next;
			// while(1);
			// printf("key is --%s\n", *env->key);
		if (!ft_strcmp(nxt->key, remove))
		{
			printf("am here\n");
			// exit(1);
			// printf("%s\n\n\n\\n", remove);
			(curent)->next = NULL;
			curent = nxt->next;
			break ;
		}
		*env = (*env)->next;
	}
	*env = tmp;
	while(*env)
	{
		printf("%s\n", (*env)->key);
		*env = (*env)->next;
	}
	exit (1);
}