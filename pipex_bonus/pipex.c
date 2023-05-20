/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 13:15:07 by werrahma          #+#    #+#             */
/*   Updated: 2023/05/20 12:46:21 by werrahma         ###   ########.fr       */
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
	int		flag;

	pipe(pipes.fd[0]);
	pipe(pipes.fd[1]);
	flag = 0;
	pipes.f0 = 0;
	pipes.f1 = 1;
	int i = 0;
	// while()
	printf("in  %d    out   %d\n", list->infile, list->outfile);
	if(list->infile > 2 && list->next)
	{
		// printf("here\n");
		chld_o = fork();
		if (chld_o == 0)
			child_process_one(list, env, &pipes);
	}
	else if (list->infile < 2 && list->next)
	{
		printf("multiple\n");
		multiple_pipe(list, env, &pipes);
	}
	if (!list->next)
	{
		printf("am here\n");
		flag = 1;
		list->outfile = 1;
	}
	if (list->outfile > 2 || flag == 1)
	{
		printf("am here\n");
		chld_t = fork();
		if (chld_t == 0)
			last_child(list, env, &pipes);
	}
	close(pipes.fd[pipes.f0][0]);
	close(pipes.fd[pipes.f0][1]);
	close(pipes.fd[pipes.f0][0]);
	close(pipes.fd[pipes.f0][1]);
	while (wait(NULL) != 1)
	return ;
}