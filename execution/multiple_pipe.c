/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:05:52 by werrahma          #+#    #+#             */
/*   Updated: 2023/06/21 17:03:11 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	forking(t_mini *list, t_pipe *pipes, t_env **env, int flag)
{
	if (flag = 1)
	{
		signal(SIGINT, handle_sig);
		first_child(list, pipes, env);
	}
	else if (flag == 3)
	{
		signal(SIGINT, handle_sig);
		last_child(list, pipes, env);
	}
}

void	check_open(t_mini *list)
{
	if (list->outfile == -1)
		write(2, "No such file or directory\n", 27);
	if (list->outfile == -1 || list->infile == -1)
		exit(1);
}
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
	{
		signal(SIGINT, handle_sig);
		second_child(list, pipes, env);
	}
	close(pipes->fd[pipes->f0][0]);
	close(pipes->fd[pipes->f0][1]);
	dup2(pipes->fd[pipes->f1][0], pipes->strin_main);
	swap(&pipes->f0, &pipes->f1);
}
