/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahamdan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 21:20:11 by yahamdan          #+#    #+#             */
/*   Updated: 2023/06/10 20:04:20 by yahamdan         ###   ########.fr       */
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


void    here_doc(char *name, char *li)
{
	char    *line;
	int     f;

	f = open(name, O_CREAT | O_RDWR | O_TRUNC, 0777);
	while (1)
	{
		//signal(SIGINT, SIG_DFL);
		// ft_putstr_fd("heredoc> ", 1);
		// line = get_next_line(0);
		line = readline("> ");
		if(!line)
		{
			//printf("\n");
			break;
		}
		if(!ft_strncmp(line, li, ft_strlen(line)) && ft_strlen(line) == ft_strlen(li))
		{
			free(line);
			break;
		}
		else
		{
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

void    open_herfiles(t_tokens *tokens)
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
			if (id == 0)
			{
				signal(SIGINT, handle_signal2);
				signal(SIGQUIT, SIG_DFL);
				name = ft_gethername();
				here_doc(name, tokens->next->cont);
				tokens->next->cont = name;
				exit(0);
			}
			waitpid(id, 0, 0);
		}
		tokens = tokens->next;
	}
}