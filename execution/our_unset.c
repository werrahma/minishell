/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 14:27:05 by werrahma          #+#    #+#             */
/*   Updated: 2023/06/21 14:43:14 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_node(t_env *env)
{
	free(env->key);
	free(env->value);
	env->key = NULL;
	env->value = NULL;
	free(env);
}

void	unset_monitor(t_var *var, t_env **env, char *remove)
{
	while (*env && (*env)->next)
	{
		var->curent = *env;
		var->nxt = (*env)->next;
		if (!ft_strcmp(var->curent->key, remove))
		{
			var->tmp1 = *env;
			*env = (*env)->next;
			var->tmp = var->tmp->next;
			free_node(var->tmp1);
			break ;
		}
		else if (!ft_strcmp(var->nxt->key, remove))
		{
			var->tmp1 = var->curent->next;
			var->curent->next = var->nxt->next;
			free_node(var->tmp1);
			break ;
		}
		*env = (*env)->next;
	}
}

int	our_unset(t_env **env, char **remove)
{
	t_var	var;
	int		i;
	int		flag2;

	var.tmp1 = NULL;
	var.curent = *env;
	var.tmp = *env;
	i = 1;
	flag2 = 0;
	while (remove[i])
	{
		unset_monitor(&var, env, remove[i]);
		if ((*env) && !(*env)->next && !ft_strcmp((*env)->key, remove[i]))
			flag2 = 1;
		*env = var.tmp;
		i++;
	}
	if (flag2 == 1)
	{
		free_node(*env);
		*env = NULL;
	}
	else
		*env = var.tmp;
	return (status_checker(0));
}
