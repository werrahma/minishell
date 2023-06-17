/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahamdan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 12:35:21 by yahamdan          #+#    #+#             */
/*   Updated: 2023/06/17 11:22:12 by yahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution/minishell.h"

char	*ft_pjoin(char *s1, char *s2)
{
	int		a;
	int		b;
	char	*m;

	a = -1;
	b = -1;
	if (!s1 && !s2)
		return (NULL);
	if (!s1 && s2)
		return ((char *)s2);
	if (s1 && !s2)
		return ((char *)s1);
	m = malloc((ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!m)
		return (0);
	while (s1[++a])
		m[a] = s1[a];
	while (s2[++b])
		m[a + b] = s2[b];
	m[a + b] = '\0';
	free(s1);
	free(s2);
	return (m);
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

char	*expand_tokens(t_tokens *token, t_env *env)
{
	int			i;
	char		*str;
	char		*s;
	char		*tmp;
	int			j;
	extern int	stx;

	i = 0;
	str = NULL;
	s = NULL;
	while (token->cont && token->cont[i])
	{
		if (token->cont[0] == '~' && token->cont[1] == '\0')
		{
			str = ft_pjoin(str, expenv("HOME", env));
		}
		else if (token->cont[i] && token->cont[i] == '$' && token->cont[i + 1] == '?'
			&& lexer_openqts(token->cont, i) != 2)
		{
			i++;;
			str = ft_pjoin(str, ft_itoa(stx));
		}
		else if (token->cont[i] && token->cont[i] == '$' && token->cont[i + 1]
			&& lexer_openqts(token->cont, i) != 2 && token->type != 4)
		{
			j = i + 1;
			i = j;
			if (!(ft_isalnum(token->cont[i])))
				str = ft_chrjoin(str, token->cont[i - 1]);
			else
			{
				while (i)
				{
					if (token->cont[i] == '\0' || !(ft_isalnum(token->cont[i])))
					{
						s = ft_substr(token->cont, j, (i - j));
						str = ft_pjoin(str, expenv(s, env));
						free(s);
						//if (!str[0] && token->cont[i] == '\0')
							//return (str);
						i--;
						break ;
					}
					i++;
				}
			}
		}
		else if (lexer_openqts(token->cont, i) == 0
			&& token->cont[i] != '\'' && token->cont[i] != '\"')
			str = ft_chrjoin(str, token->cont[i]);
		else if (lexer_openqts(token->cont, i) == 1 && token->cont[i] == '\'')
			str = ft_chrjoin(str, token->cont[i]);
		else if (lexer_openqts(token->cont, i) == 2 && token->cont[i] == '\"')
			str = ft_chrjoin(str, token->cont[i]);
		else if (token->cont[i] != '\"' && token->cont[i] != '\'')
			str = ft_chrjoin(str, token->cont[i]);
		printf("%c\n", token->cont[i]);
		i++;
	}
	if (str && str[0] == '\0' && token->perv && ( token->perv->type == 6
			|| token->perv->type == 7 || token->perv->type == 8))
	{
		tmp = ft_strjoin(token->cont, ": ");
		ft_putstr_fd(tmp, 2);
		ft_putstr_fd("ambiguous redirect\n", 2);
		stx = 1;
		free(tmp);
		token->emg = 1;
	}
	return (str);
}

void	do_expand_tokens(t_tokens **tokens, t_env *env)
{
	t_tokens	*tmp;
	char		*str;

	tmp = *tokens;
	while (*tokens)
	{
		if ((*tokens)->type == LIMETER && qoutesordlr(*tokens) == 1)
			(*tokens)->qh = 1;
		if (qoutesordlr(*tokens))
		{
			str = expand_tokens(*tokens, env);
			free((*tokens)->cont);
			(*tokens)->cont = str;
		}
		*tokens = (*tokens)->next;
	}
	*tokens = tmp;
}
