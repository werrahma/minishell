/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <werrahma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 13:15:07 by werrahma          #+#    #+#             */
/*   Updated: 2023/05/23 23:12:19 by werrahma         ###   ########.fr       */
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
	static int check;
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
	printf("%dn", list->infile);
	printf("\n*******************\n");
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
		// printf("%d\n", pipes->stdiin);
		// printf("get == %s\n", get_next_line(pipes->fd[0][0]));
		printf("am here\n");
		dup2(pipes->fd[pipes->f0][0], pipes->stdiin);
	}
	else if (list->infile < 2 && list->next)
	{
		printf("multiple\n");
		multiple_pipe(list, env, pipes);
	}
	else if (!list->next && list->outfile < 2)
	{
		// printf("am here\n");
		flag = 1;
		list->outfile = pipes->stdouut;
	}
	if (list->outfile > 2 || flag == 1)
	{
		// dprintf (2, "^^^%s\n", get_next_line(pipes->fd[0][1]));
		pipes->check = 0;
		printf("i have outfile\n");
		chld_t = fork();
		if (chld_t == 0)
			last_child(list, env, pipes);
	}
	// dprintf(2, "$$$$$$$$$$%s/n", get_next_line(pipes->fd[0][0]));
	// close(pipes->fd[0][0]);
	// close(pipes->fd[0][1]);
	close(pipes->fd[pipes->f0][0]);
	close(pipes->fd[pipes->f0][1]);
	close(pipes->fd[pipes->f1][0]);
	close(pipes->fd[pipes->f1][1]);
	while (wait(NULL) != -1)
		continue;

	// return ;
}
