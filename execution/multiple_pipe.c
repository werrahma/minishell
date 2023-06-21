/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:05:52 by werrahma          #+#    #+#             */
/*   Updated: 2023/06/21 11:41:29 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_failure(t_mini *list, int flag, t_pipe *pipes, t_env **env)
{
	int	i;

	i = 0;
	if (flag == -1)
	{
		while (list->cmd[i])
		{
			printf("minishell: %s No such file or directory\n",
				list->cmd[i++]);
		}
		exit(1);
	}
	else
	{
		if (flag == 1)
			check_arg(list->cmd, env);
		colse_files(pipes);
		if (flag == 1 || !list->cmd[0])
			exit(0);
	}
}

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
