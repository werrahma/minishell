/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_help.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 19:47:06 by werrahma          #+#    #+#             */
/*   Updated: 2023/02/20 22:16:02 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	h_d_help(char **av, char **env, int ac, t_pipe *pipes)
{
	int	i;
	int	id1;

	i = 4;
	while (i < ac - 2)
	{
		id1 = fork();
		if (id1 == 0)
			h_c_child_process_two(av, env, pipes, i);
		close(pipes->fd[pipes->f0][0]);
		close(pipes->fd[pipes->f0][1]);
		pipe(pipes->fd[pipes->f0]);
		swap(&pipes->f0, &pipes->f1);
		i++;
	}
}
