/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:05:52 by werrahma          #+#    #+#             */
/*   Updated: 2023/05/18 12:38:00 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	help(char **av, char **env, int ac, t_pipe *pipes)
{
	int	i;
	int	id1;

	i = 3;
	while (i < ac - 2)
	{
		id1 = fork();
		if (id1 == 0)
			child_process_two(av, env, pipes, i);
		close(pipes->fd[pipes->f0][0]);
		close(pipes->fd[pipes->f0][1]);
		pipe(pipes->fd[pipes->f0]);
		swap(&pipes->f0, &pipes->f1);
		i++;
	}
}
