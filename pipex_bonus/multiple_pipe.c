/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:05:52 by werrahma          #+#    #+#             */
/*   Updated: 2023/05/20 11:06:11 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//void	multiple_pipe(t_mini *list, char **env, int ac, t_pipe *pipes)
void	multiple_pipe(t_mini *list, char **env, t_pipe *pipes)
{
	int	i;
	int	id1;
	int ac = 0;

	i = 3;
	// while (list->infile == 0)
	// {
	// printf("hna\n");
		id1 = fork();
		if (id1 == 0)
			child_process_two(list, env, pipes);
		// return ;
		close(pipes->fd[pipes->f0][0]);
		close(pipes->fd[pipes->f0][1]);
		pipe(pipes->fd[pipes->f0]);
		// return ;
		swap(&pipes->f0, &pipes->f1);
	// 	i++;
	// }
}
