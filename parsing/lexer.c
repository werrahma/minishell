/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahamdan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:44:16 by yahamdan          #+#    #+#             */
/*   Updated: 2023/05/05 16:12:40 by yahamdan         ###   ########.fr       */
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


// t_lexer *lexer_init(char *line)
// {
// 	t_lexer	*lexer;

// 	lexer = maloc(sizeof(t_lexer));
	
// 	lexer->content = line;
// 	lexer->i = 0;
// 	lexer->c = line[lexer->i];

// 	return (lexer);
// }

char	*lexer_collect_str(char *line , int *i)
{
	char *str;

	str = NULL;
	while(!sep(line[*i]))
	{
		str = ft_chrjoin(str, line[*i]);
		(*i)++;
	}
	return (str);
}

char * lexer_collect_op(char *line, int *i)
{
	char	*str;

	while (line[*i] == ' ')
		*i += 1;
	if (sep(line[*i]) && !sep(line[*i + 1]))
		return (ft_chrjoin(str, line[*i++]));
	
	else if (sep(line[*i]) && sep(line[*i + 1]))
	{
		str = ft_chrjoin(str, line[*i++]);
		if (line[*i] == '>' && line[*i - 1] == '>')
			str = ft_chrjoin(str, line[*i++]);
		else if (line[*i] == '<' && line[*i - 1] == '<')
			str = ft_chrjoin(str, line[*i++]);
		else
			return (str);
	}
	return (str);
}

t_tokens	*lexer_split_cmdline(char *line)
{
	t_tokens	*token;
	t_tokens	*tmp;
	int		i;
	char	*str;
	i = 0;
	token = malloc(sizeof(t_tokens));
	tmp = token;
	while(line[i])
	{
		if (!sep(line[i]))
		{
			ft_lstadd_back(&token, ft_lstnew(lexer_collect_str(line, &i)));
		}
		else if (sep(line[i]))
			ft_lstadd_back(&token, ft_lstnew(lexer_collect_op(line, &i)));
	}
	token = tmp;
	return (token);
}



