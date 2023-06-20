/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:05:52 by werrahma          #+#    #+#             */
/*   Updated: 2023/06/19 21:06:55 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	multiple_pipe(t_mini *list, t_env **env, t_pipe *pipes)
{
	pipes->pid[pipes->index] = fork();
	if (pipes->pid[pipes->index] == 0)
		second_child(list, pipes, env);
	close(pipes->fd[pipes->f0][0]);
	close(pipes->fd[pipes->f0][1]);
	dup2(pipes->fd[pipes->f1][0], pipes->strin_main);
	swap(&pipes->f0, &pipes->f1);
}
