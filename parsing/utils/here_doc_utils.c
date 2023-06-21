/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahamdan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 21:42:53 by yahamdan          #+#    #+#             */
/*   Updated: 2023/06/20 21:46:48 by yahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../execution/minishell.h"

char	*ft_gethername(void)
{
	char	*name;
	int		i;
	char	*ii;

	i = 0;
	ii = ft_itoa(i);
	name = ft_strjoin("/tmp/here_doc", ii);
	while (!access(name, F_OK))
	{
		free(name);
		free(ii);
		i++;
		ii = ft_itoa(i);
		name = ft_strjoin("/tmp/here_doc", ii);
	}
	free(ii);
	return (name);
}

void	free_tmp(char *name, t_tokens *tokens)
{
	free(name);
	free(tokens->next->cont);
	tokens->next->cont = NULL;
}

char	*herexpand(char *line, char *str, int *i, t_env *env)
{
	int		j;
	char	*s;

	s = NULL;
	j = *i + 1;
	*i = j;
	while (*i)
	{
		if (line[*i] == '\0' || !(ft_isalnum(line[*i])))
		{
			s = ft_substr(line, j, (*i - j));
			str = ft_strjoin(str, expenv(s, env));
			free(s);
			if (!str[0] && line[*i] == '\0')
				return (str);
			(*i)--;
			break ;
		}
		(*i)++;
	}
	return (str);
}
