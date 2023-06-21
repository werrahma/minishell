/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:13:30 by werrahma          #+#    #+#             */
/*   Updated: 2023/06/21 09:27:36 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_env(char *str)
{
	char	*tmp;
	char	**split;
	int		i;
	int		j;

	j = 0;
	split = malloc(sizeof(char **) * 3);
	i = 0;
	while (str[i] != '=')
		i++;
	split[0] = malloc(i + 1);
	while (j < i)
	{
		split[0][j] = str[j];
		j++;
	}
	split[0][i] = '\0';
	split[1] = ft_strdup (&str[i + 1]);
	split[2] = NULL;
	return (split);
}
