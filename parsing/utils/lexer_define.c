/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_define.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahamdan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 11:10:44 by yahamdan          #+#    #+#             */
/*   Updated: 2023/06/18 11:18:25 by yahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../execution/minishell.h"

int	definetype_helper(t_tokens *toke)
{
	if (!ft_strcmp(toke->cont, "<<"))
		return (HEREDOC);
	else if (!ft_strcmp(toke->cont, "<"))
		return (INPUT);
	else if (!ft_strcmp(toke->cont, ">"))
		return (OUTPUT);
	else if (!ft_strcmp(toke->cont, ">>"))
		return (APPEND);
	else if (!ft_strcmp(toke->cont, "|"))
		return (PIPE);
	else if (!toke->perv)
		return (ARG);
	else if (toke->perv->type == HEREDOC)
		return (LIMETER);
	else if (toke->perv->type == INPUT)
		return (INFILE);
	else if (toke->perv->type == OUTPUT)
		return (OUTFILE);
	else if (toke->perv->type == APPEND)
		return (OUTFILE);
	else
		return (ARG);
}

t_tokens	*lexer_definetype(t_tokens *token)
{
	t_tokens	*tmp;

	tmp = token;
	while (token)
	{
		token->type = definetype_helper(token);
		token = token->next;
	}
	token = tmp;
	return (token);
}
