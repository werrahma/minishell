/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <werrahma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 13:15:07 by werrahma          #+#    #+#             */
/*   Updated: 2023/05/26 21:17:15 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	pipex(t_mini *list, char **env, t_pipe *pipes)
{
	// t_pipe	pipes;
	int		chld_o;
	int		chld_t;
	int		flag;
	int a;

	a = 0;
	flag = 0;
	int i = 0;
	if (!list->next && list->outfile < 2)
	{
		printf("am here for flag\n");
		flag = 1;
		list->outfile = 1;
	}
	if(list->infile > 2)
	{
		a++;
		printf("i have infile\n");
		chld_o = fork();
		if (chld_o == 0)
			child_process_one(list, env, pipes);
	}
	if (a > 0)
	{
		printf("am here\n");
		dup2(pipes->fd[pipes->f0][0], pipes->strin_main);
	}
	else if (list->infile < 2 && list->next && list->outfile < 2)
	{
		printf("multiple\n");
		multiple_pipe(list, env, pipes);
	}
	else if (list->outfile > 2 || flag == 1)
	{
		printf("i have outfile\n");
		chld_t = fork();
		if (chld_t == 0)
			last_child(list, env, pipes);
	}
	close(pipes->fd[pipes->f0][0]);
	close(pipes->fd[pipes->f0][1]);
	close(pipes->fd[pipes->f1][0]);
	close(pipes->fd[pipes->f1][1]);
	while (wait(NULL) != -1)
		continue;
}
