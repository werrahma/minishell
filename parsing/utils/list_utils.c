/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahamdan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 10:20:01 by yahamdan          #+#    #+#             */
/*   Updated: 2023/06/18 11:06:32 by yahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../execution/minishell.h"

void	ft_lstadd_backl(t_mini **lst, t_mini *new)
{
	t_mini	*tmp;

	tmp = ft_lstlastl(*lst);
	if (!lst || !new)
		return ;
	if (*lst == NULL )
		(*lst) = new;
	else
		ft_lstlastl(*lst)->next = new;
}

t_mini	*ft_lstnewl(void)
{
	t_mini	*lst;

	lst = malloc(sizeof(t_mini));
	if (!lst)
		return (NULL);
	lst->next = NULL;
	lst->cmd = NULL;
	lst->infile = -3;
	lst->outfile = -3;
	return (lst);
}

t_mini	*ft_lstlastl(t_mini *lst)
{
	if (!lst)
		return (NULL);
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	free_tokens(t_tokens *t)
{
	t_tokens	*tmp;

	while (t)
	{
		tmp = t;
		t = t->next;
		free(tmp->cont);
		free(tmp);
	}
}

void	*ft_realloc(void *ptr, size_t size)
{
	void	*nptr;
	size_t	len;

	if (ptr == NULL)
	{
		ptr = malloc(size);
		return (ptr);
	}
	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	nptr = malloc(size);
	if (!nptr)
		return (NULL);
	len = size;
	ft_memcpy(nptr, ptr, len);
	free(ptr);
	return (nptr);
}
