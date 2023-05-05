/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 21:00:18 by werrahma          #+#    #+#             */
/*   Updated: 2023/05/05 10:13:25 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

void	ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while ((*lst)->next)
		*lst = (*lst)->next;
	(*lst)->next = new;
	new->next = NULL;
	*lst = tmp;
}
