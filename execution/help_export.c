/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 18:10:39 by werrahma          #+#    #+#             */
/*   Updated: 2023/06/20 20:17:16 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_spas_instring(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (str[i] == ' ' || str[i] == '-' || (str[0] >= '0' && str[0] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

void	free_env(t_env **env)
{
	t_env	*tmp;

	while (*env)
	{
		tmp = *env;
		free((*env)->key);
		free((*env)->value);
		*env = (*env)->next;
		free(tmp);
	}
}

t_env	*fond_key(t_env *list, char *str)
{
	while (list)
	{
		if (!ft_strncmp(list->key, str, ft_strlen(list->key)))
			return (list);
		list = list->next;
	}
	return (NULL);
}

void	dup_value(char *str, t_env *lst)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
		i++;
	j = i;
	while (str[j])
		j++;
	lst->value = malloc(j + 1);
	j = 0;
	while (str[i])
	{
		lst->value[j] = str[i];
		i++;
		j++;
	}
	if (j == 0)
	{
		free(lst->value);
		lst->value = NULL;
	}
	else
		lst->value[j] = '\0';
}

void	dup_key(char *str, t_env *lst)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[j] && str[j] != '=')
		j++;
	if (str[j] && !str[j + 1])
		j++;
	lst->key = malloc(j + 1);
	while (str && i < j)
	{
		lst->key[i] = str[i];
		i++;
	}
	lst->key[i] = '\0';
}
