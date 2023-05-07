/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahamdan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:44:16 by yahamdan          #+#    #+#             */
/*   Updated: 2023/05/06 20:16:30 by yahamdan         ###   ########.fr       */
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
	while(!sep(line[*i]) && line[*i])
	{
		str = ft_chrjoin(str, line[*i]);
		(*i)++;
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
			ft_lstadd_back(&token, ft_lstnew(lexer_collect_str(line, &i)));
		else if (sep(line[i]))
		{
			ft_lstadd_back(&token, ft_lstnew(lexer_collect_op(line, &i)));
		}
	}
	return (token);
}
