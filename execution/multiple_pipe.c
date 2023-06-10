/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:05:52 by werrahma          #+#    #+#             */
/*   Updated: 2023/06/10 15:15:42 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//void	multiple_pipe(t_mini *list, char **env, int ac, t_pipe *pipes)
void	multiple_pipe(t_mini *list, t_env **env, t_pipe *pipes)
{
	int			i;
	int			id1;
	int			ac;
	static int	check;

	ac = 0;
	i = 3;
	// while (list->infile == 0)
	// {
	pipes->pid[pipes->index] = fork();
	if (pipes->pid[pipes->index] == 0)
		second_child(list, pipes, env);
	// printf("hna\n");
	// return ;
	close(pipes->fd[pipes->f0][0]);
	close(pipes->fd[pipes->f0][1]);
	dup2(pipes->fd[pipes->f1][0], pipes->strin_main);
	// pipe(pipes->fd[pipes->f0]);
	check++;
	swap(&pipes->f0, &pipes->f1);
	// }
}
