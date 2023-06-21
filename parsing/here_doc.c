/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahamdan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 21:20:11 by yahamdan          #+#    #+#             */
/*   Updated: 2023/06/20 20:14:26 by yahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution/minishell.h"

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
	return(str);
}

char	*expand_her(char *line, t_env *env)
{
	int		i;
	int		j;
	char	*s;
	char	*str;

	i = 0;
	s = NULL;
	str = NULL;
	while (line[i])
	{
		if (line[i] == '$' && !(ft_isalnum(line[i + 1])))
				str = ft_chrjoin(str, line[i]);
		else if (line[i] == '$')
		{
			str = herexpand(line, str, &i, env);
			if (!str[0] && line[i] == '\0')
				return (free(line), str);
		
		}
		else
			str = ft_chrjoin(str, line[i]);
		i++;
	}
	free(line);
	return (str);
}

void	handle_signal2(int sig)
{
	printf("\n");
	exit(1);
}

int	here_doc(char *name, char *li, int qh, t_env *env)
{
	char	*line;
	int		f;

	f = open(name, O_CREAT | O_RDWR | O_TRUNC, 0777);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strncmp(line, li, ft_strlen(line))
			&& ft_strlen(line) == ft_strlen(li))
			return (free(line), f);
		else
		{
			if (qh == 1 || !ft_strchr(line, '$'))
				;
			else
				line = expand_her(line, env);
			ft_putstr_fd(line, f);
			ft_putchar_fd('\n', f);
			free(line);
		}
	}
	return (f);
}

void	dochelper(t_tokens *tokens, char *name, t_env *list)
{
	int	f;

	signal(SIGINT, handle_signal2);
	signal(SIGQUIT, SIG_IGN);
	f = here_doc(name, tokens->next->cont, tokens->next->qh, list);
	close(f);
	exit(0);
}

void	free_tmp(char *name, t_tokens *tokens)
{
	free(name);
	free(tokens->next->cont);
	tokens->next->cont = NULL;
}

void	open_herfiles(t_tokens *tokens, t_env *list)
{
	int			id;
	char		*name;
	int			status;
	int			f;

	while (tokens)
	{
		if (tokens->type == HEREDOC)
		{
			signal(SIGINT, SIG_IGN);
			name = ft_gethername();
			id = fork();
			if (id == 0)
				dochelper(tokens, name, list);
			waitpid(id, &status, 0);
			if (status != 0)
			{
				free_tmp(name, tokens);
				break ;
			}
			free(tokens->next->cont);
			tokens->next->cont = name;
		}
		tokens = tokens->next;
	}
}
