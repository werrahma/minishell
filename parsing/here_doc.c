/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahamdan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 21:20:11 by yahamdan          #+#    #+#             */
/*   Updated: 2023/06/11 20:07:49 by yahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution/minishell.h"

char	*ft_gethername()
{
	char	*name;
	int 	i;
	char 	*ii;

	i = 0;
	ii = ft_itoa(i);
	name = ft_strjoin("/tmp/here_doc", ii);
	while (!access(name, F_OK))
	{
		i++;
		ii = ft_itoa(i);
		name = ft_strjoin("/tmp/here_doc", ii);
	}
	return (name);
}
char	*expand_her(char *line, t_env *env)
{
	int i;
	int j;
	char *s = NULL;
	char *str = NULL;

	i = 0;
	while(line[i])
	{
		if (line[i] == '$' && !(ft_isalnum(line[i + 1])))
				str = ft_chrjoin(str, line[i]);
		else if(line[i] == '$')
		{
			j = i + 1;
			i = j;
			while (i)
			{
				if (line[i] == '\0' || !(ft_isalnum(line[i])))
				{
					s = ft_substr(line, j , (i - j));
					str = ft_strjoin(str, expenv(s, env));
					if (!str[0] && line[i] == '\0')
						return (str);
					i--;
					break;
				}
				i++;
			}
		}
		else
 			str = ft_chrjoin(str, line[i]);
		i++;
	}
	return (str);
}
void    here_doc(char *name, char *li, int qh, t_env *env)
{
	char    *line;
	int     f;

	f = open(name, O_CREAT | O_RDWR | O_TRUNC, 0777);
	while (1)
	{
		line = readline("> ");
		if(!line)
			break;
		if(!ft_strncmp(line, li, ft_strlen(line)) && ft_strlen(line) == ft_strlen(li))
		{
			//printf("here\n");
			free(line);
			break;
		}
		else
		{
			if (qh == 1 || !ft_strchr(line, '$'));
			else
				line = expand_her(line, env);
			ft_putstr_fd(line, f);
			ft_putchar_fd('\n', f);
		}
		free (line);
	}
}

void handle_signal2(int sig)
{
	printf("\n");
	exit(0);
}

void    open_herfiles(t_tokens *tokens, t_env *list)
{
	int id;
	extern int stx;
	char	*name;

	while(tokens)
	{
		if(tokens->type == HEREDOC)
		{	
			signal(SIGINT, SIG_IGN);
			id = fork();
			name = ft_gethername();
			if (id == 0)
			{
				signal(SIGINT, handle_signal2);
				signal(SIGQUIT, SIG_DFL);
				here_doc(name, tokens->next->cont, tokens->next->qh, list);
				exit(0);
			}
			waitpid(id, 0, 0);
			free(tokens->next->cont);
			tokens->next->cont = name;
		}
		tokens = tokens->next;
	}
}