/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <werrahma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:05:52 by werrahma          #+#    #+#             */
/*   Updated: 2023/05/21 18:40:28 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//void	multiple_pipe(t_mini *list, char **env, int ac, t_pipe *pipes)
void	multiple_pipe(t_mini *list, char **env, t_pipe *pipes)
{
	int	i;
	int	id1;
	int ac = 0;

	i = 3;
	// while (list->infile == 0)
	// {
		id1 = fork();
		if (id1 == 0)
			child_process_two(list, env, pipes);
	// printf("hna\n");
		// return ;
		close(pipes->fd[pipes->f0][0]);
		close(pipes->fd[pipes->f0][1]);
		pipe(pipes->fd[pipes->f0]);
		swap(&pipes->f0, &pipes->f1);
	// 	i++;
	// }
}
