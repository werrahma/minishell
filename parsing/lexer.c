/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahamdan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:44:16 by yahamdan          #+#    #+#             */
/*   Updated: 2023/06/12 10:59:07 by yahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution/minishell.h"

int sep(char s)
{
	if (s == '<' || s == '>' || s == '|')
		return (1);
	else if (s == ' ' || s == '\n' || s == '\t')
		return (1);
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
		//printf("%d\n", token->type);
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

char	*lexer_collect_str(char *line, int *i)
{
	char *str = NULL;

	while(line[*i])
	{
		if (sep(line[*i]) && lexer_openqts(line, *i) == 0)
		{
			return (str);
		}
		else if (lexer_openqts(line, *i) == 0 && line[*i] != '\'' && line[*i] != '\"' &&  !sep(line[*i]))
			str = ft_chrjoin(str, line[*i]);
		else if (lexer_openqts(line, *i) == 1 && line[*i] == '\'')
			str = ft_chrjoin(str, line[*i]);
		else if (lexer_openqts(line, *i ) == 2 && line[*i] == '\"')
			str = ft_chrjoin(str, line[*i]);
		else
			str = ft_chrjoin(str, line[*i]);
		(*i)++;
	}
	return (str);
}

// char	*lexer_collect_str(char *line, int *i)
// {
// 	char *str = NULL;
	
// 	while(!sep(line[*i]) && line[*i])
// 	{
// 		if (lexer_openqts(line, *i) == 0 && line[*i] != '\'' && line[*i] != '\"')
// 			str = ft_chrjoin(str, line[*i]);
// 		else if (lexer_openqts(line, *i) == 1 && line[*i] == '\'')
// 			str = ft_chrjoin(str, line[*i]);
// 		else if (lexer_openqts(line, *i) == 2 && line[*i] == '\"')
// 			str = ft_chrjoin(str, line[*i]);
// 		else if (line[*i] != '\"' && line[*i] != '\'')
// 			str = ft_chrjoin(str, line[*i]);
// 		(*i)++;
// 	}
// 	return (str);
// }

char * lexer_collect_op(char *line, int *i)
{
	char	*str = NULL;

	if (sep(line[*i]) && (!sep(line[*i + 1]) || (line[*i + 1] == ' ' || line[*i + 1] == '\t')))
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
		if (line[i] == ' ' || line[i] == '\t')
			i++; 
		else if (!sep(line[i]))
		{
			ft_lstadd_backp(&token, ft_lstnewp(lexer_collect_str(line, &i)));
		}
		else if (sep(line[i]))
		{
			ft_lstadd_backp(&token, ft_lstnewp(lexer_collect_op(line, &i)));
		}
	}
	lexer_definetype(token);
	// stxe(token);
	return (token);
}
