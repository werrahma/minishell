/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 22:45:28 by werrahma          #+#    #+#             */
/*   Updated: 2023/06/21 20:09:26 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*tab_pid(t_mini *list)
{
	int	*tab;

	tab = malloc(sizeof(int) * ft_lstsize(list));
	return (tab);
}

void	handle_sig(int sig)
{
	(void)sig;
	printf("\n");
}

int	if_stdout(t_mini *list)
{
	int	flag;

	flag = 0;
	if (!list->next && list->outfile == -3)
	{
		flag = 1;
		list->outfile = 1;
	}
	return (flag);
}

void	colse_files(t_pipe *pipes)
{
	close(pipes->fd[pipes->f0][0]);
	close(pipes->fd[pipes->f0][1]);
	close(pipes->fd[pipes->f1][0]);
	close(pipes->fd[pipes->f1][1]);
}

void	pipes_monitor(t_mini *list, t_pipe *pipes, t_env **env)
{
	int	flag;
	int	have_file;

	have_file = 0;
	flag = 0;
	flag = if_stdout(list);
	if (list->infile > 2 || list->infile == -1 || list->outfile == -1)
	{
		have_file++;
		pipes->pid[pipes->index] = fork();
		if (pipes->pid[pipes->index] == 0)
			forking(list, pipes, env, 1);
	}
	if (have_file > 0)
		dup2(pipes->fd[pipes->f0][0], pipes->strin_main);
	else if (list->infile == -3 && list->next && list->outfile == -3)
		multiple_pipe(list, env, pipes);
	else if (list->outfile > 2 || flag == 1)
	{
		pipes->pid[pipes->index] = fork();
		if (pipes->pid[pipes->index] == 0)
			forking(list, pipes, env, 3);
	}
	colse_files(pipes);
}
