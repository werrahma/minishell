/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 21:20:11 by yahamdan          #+#    #+#             */
/*   Updated: 2023/06/07 13:31:22 by werrahma         ###   ########.fr       */
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
		ft_putstr_fd("heredoc> ", 1);
		line = get_next_line(0);
		if(!line)
		{
			printf("\n");
			break;
		}
		if(!ft_strncmp(line, li, ft_strlen(line) - 1) && ft_strlen(line) - 1 == ft_strlen(li))
		{
			free(line);
			break;
		}
		else
			ft_putstr_fd(line, f);
		free (line);
	}
}

void    open_herfiles(t_tokens *tokens)
{
	int id;
	char	*name;

	while(tokens)
	{
		if(tokens->type == HEREDOC)
		{
			//id = fork();
			//if (id == 0)
			//{
				name = ft_gethername();
				here_doc(name, tokens->next->cont);
				tokens->next->cont = name;
			//}
			//waitpid(id, 0, 0);
		}
		tokens = tokens->next;
	}
}