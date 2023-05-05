/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 12:08:24 by werrahma          #+#    #+#             */
/*   Updated: 2023/05/05 13:42:59 by werrahma         ###   ########.fr       */
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