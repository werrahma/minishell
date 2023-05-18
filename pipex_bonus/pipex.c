/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <werrahma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 13:15:07 by werrahma          #+#    #+#             */
/*   Updated: 2023/05/18 23:29:00 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	pipex(t_mini *list, char **env)
{
	t_pipe	pipes;
	int		chld_o;
	int		chld_t;

	pipe(pipes.fd[0]);
	pipe(pipes.fd[1]);
	if(list->infile > 2)
	{
		chld_o = fork();
		if (chld_o == 0)
			child_process_one(list, env, &pipes);
	}
	else if (list->infile == 0)
		multiple_pipe(list, env, &pipes);
	else if (list->infile > 2)
	{
		chld_t = fork();
		if (chld_t == 0)
			last_child(list, env, &pipes);
	}
	close(pipes.fd[pipes.f0][0]);
	close(pipes.fd[pipes.f0][1]);
	close(pipes.fd[pipes.f0][0]);
	close(pipes.fd[pipes.f0][1]);
	while (wait(NULL) != 1)
	exit(0);
}