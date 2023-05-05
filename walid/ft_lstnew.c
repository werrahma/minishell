/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 13:59:08 by werrahma          #+#    #+#             */
/*   Updated: 2023/05/05 11:37:37 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_lstnew(int content)
{
	t_env	*new;

	new = NULL;
	new = malloc(sizeof(t_env));
	new->data = content;
	new->next = NULL;
	return (new);
}
