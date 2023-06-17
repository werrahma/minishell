/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stxe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahamdan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:19:35 by yahamdan          #+#    #+#             */
/*   Updated: 2023/06/17 13:17:46 by yahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution/minishell.h"

void	ft_maxheropn(t_tokens *tokens)
{
	int	i;

	i = 0;
	while (tokens)
	{
		if (tokens->type == HEREDOC)
			i++;
		tokens = tokens->next;
	}
	if (i > 16)
	{
		ft_putstr_fd("maximum here-document count exceeded\n", 2);
		exit(2);
	}
}

int	stxe(t_tokens *to)
{
	extern int	stx;
	int j = 0;

	if (to && to->type == 2)
	{
		ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
		stx = 258;
		return (1);
	}
	while (to)
	{
		if (to->type == 2)
			j++;
		if ((to->type == 6 || to->type == 7 || to->type == 2
				|| to->type == 3 || to->type == 8) && (!to->next))
		{
			ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
			stx = 258;
			return (1);
		}
		else if ((to->type == 3 && to->next->type != 4)
			|| (to->type == 6 && to->next->type != 0)
			|| (to->type == 7 && to->next->type != 1)
			|| (to->type == 8 && to->next->type != 1)
			|| (to->type == 2 && to->next->type == 2))
		{
			write(2, "syntax error near unexpected token `", 37);
			ft_putstr_fd(ft_strjoin(to->next->cont, "\'\n"), 2);
			stx = 258;
			return (1);
		}
		to = to->next;
	}
	if (j > 1050)
	{
		ft_putstr_fd("fork: Resource temporarily unavailable\n", 2);
		stx = 1;
		return (1);
	}
	return (0);
}
