/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <werrahma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 13:15:07 by werrahma          #+#    #+#             */
/*   Updated: 2023/05/22 22:27:12 by werrahma         ###   ########.fr       */
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
	// pipe(pipes->fd[0]);
	// pipe(pipes->fd[1]);
	// if (a > 0)
	// {
	// 	printf("aaa\n");
	// 	dup2(pipes->fd[pipes->f0][0], 0);
	// 	// dup2(list->outfile, 1);
	// 	execve("/usr/bin/cat", list->cmd, env);
	// 		close(pipes->fd[pipes->f0][0]);
	// close(pipes->fd[pipes->f0][1]);
	// close(pipes->fd[pipes->f1][0]);
	// close(pipes->fd[pipes->f1][1]);
	// 	return ;
	// }
	flag = 0;
	// pipes->f0 = 0;
	// pipes->f1 = 1;
	int i = 0;
	// while()
	// printf("in  %d    out   %d\n", list->infile, list->outfile);
	// while(list->cmd[i])
	// 	printf("%s\n", list->cmd[i++]);
	// return ;
	if(list->infile > 2)
	{
		a++;
		printf("i have infile\n");
		chld_o = fork();
		if (chld_o == 0)
			child_process_one(list, env, pipes);
	}
	if ((list->infile == -3 && a > 0 || a > 0))
	{
		// printf("%d\n", pipes->stdiin);
		// printf("get == %s\n", get_next_line(pipes->fd[0][0]));
		if(!dup2(pipes->fd[0][0], pipes->stdiin))
			write(2, "failed\n", 7);
		// printf("am here\n");
	}
	else if (list->infile < 2 && list->next)
	{
		printf("multiple\n");
		multiple_pipe(list, env, pipes);
	}
	if (!list->next && list->outfile < 2)
	{
		// printf("am here\n");
		flag = 1;
		list->outfile = 1;
	}
	if (list->outfile > 2 || flag == 1)
	{
		// dprintf (2, "^^^%s\n", get_next_line(pipes->fd[0][1]));
		printf("i have outfile\n");
		chld_t = fork();
		if (chld_t == 0)
			last_child(list, env, pipes);
	}
	// dprintf(2, "$$$$$$$$$$%s/n", get_next_line(pipes->fd[0][0]));
	close(pipes->fd[0][0]);
	close(pipes->fd[0][1]);
	close(pipes->fd[pipes->f1][0]);
	close(pipes->fd[pipes->f1][1]);
	while (wait(NULL) != -1)
		continue;

	// return ;
}