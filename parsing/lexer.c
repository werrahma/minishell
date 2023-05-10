/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahamdan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:44:16 by yahamdan          #+#    #+#             */
/*   Updated: 2023/05/08 20:21:47 by yahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int sep(char s)
{
	if (s == '<' || s == '>')
		return (1);
	else if (s == ' ' || s == '\n')
		return (1);
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	a;

	a = 0;
	while (s1[a] || s2[a])
	{
		if (s1[a] != s2[a])
			return ((unsigned char)s1[a] - (unsigned char)s2[a]);
		a++;
	}
	return (0);
}

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
		return(ARG);
}

t_tokens	*lexer_definetype(t_tokens *token)
{
	t_tokens *tmp;
	tmp = token;

	while(token)
	{
		token->type = definetype_helper(token);
		token = token->next;
	}
	token = tmp;
	return (token);
}

int	lexer_openqts(char	*line, int indx)
{
	int	i;
	int op;

	i = 0;
	op = 0;
	while(line[i] && i != indx)
	{
		if (op == 0 && line[i] == '\"')
			op = 1;
		else if (op == 0 && line[i] == '\'')
			op = 2;
		else if (op == 1 && line[i] == '\"')
			op = 0;
		else if (op == 2 && line[i] == '\'')
			op = 0;
		i++;
	}
	return (op);
}

char	*lexer_collect_str(char *line , int *i)
{
	char *str;

	str = NULL;
	if (line[*i] == '\'' || line[*i] == '\"')
	{
		(*i)++;
		while(line[*i] && lexer_openqts(line, *i) != 0)
		{
			if (lexer_openqts(line, *i + 1) != 0)
				str = ft_chrjoin(str, line[*i]);
			(*i)++;
		}
	}
	else
	{
		while(!sep(line[*i]) && line[*i])
		{
			str = ft_chrjoin(str, line[*i]);
			(*i)++;
		}
	}
	return (str);
}

char * lexer_collect_op(char *line, int *i)
{
	char	*str = NULL;

	if (sep(line[*i]) && (!sep(line[*i + 1]) || line[*i + 1] == ' '))
	{
		str = ft_chrjoin(str, line[(*i)++]);
	}
	else if (sep(line[*i]) && sep(line[*i + 1]))
	{
		str = ft_chrjoin(str, line[(*i)++]);
		if (str[0] == line[*i])
			str = ft_chrjoin(str, line[(*i)++]);
		else
			return (str);
	}
	return (str);
}

t_tokens	*lexer_split_cmdline(char *line)
{
	t_tokens	*token;
	int		i;
	char	*str;
	i = 0;
	token = NULL;
	while(line[i])
	{
		if (line[i] == ' ')
			i++; 
		else if (!sep(line[i]))
		{
			ft_lstadd_back(&token, ft_lstnew(lexer_collect_str(line, &i)));
			
		}
		else if (sep(line[i]))
		{
			ft_lstadd_back(&token, ft_lstnew(lexer_collect_op(line, &i)));
		}
	}
	lexer_definetype(token);
	return (token);
}
