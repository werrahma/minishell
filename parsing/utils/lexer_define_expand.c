/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_define_and_expand.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahamdan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 11:10:44 by yahamdan          #+#    #+#             */
/*   Updated: 2023/06/21 13:05:30 by yahamdan         ###   ########.fr       */
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

int	qoutesordlr(t_tokens *token)
{
	int	i;

	i = 0;
	while (token->cont[i])
	{
		if (token->cont[i] == '\'' || token->cont[i] == '\"')
			return (1);
		if (token->cont[i] == '$' || token->cont[i] == '~')
			return (2);
		i++;
	}
	return (0);
}

char	*expenv(char *str, t_env *env)
{
	t_env	*rmp;

	rmp = env;
	while (env)
	{
		if (ft_strcmp(str, env->key) == 0)
			return (ft_strdup(env->value));
		env = env->next;
	}
	env = rmp;
	return (ft_strdup(""));
}
