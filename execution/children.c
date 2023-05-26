/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 19:12:49 by werrahma          #+#    #+#             */
/*   Updated: 2023/05/26 12:34:19 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// # include "../execution/minishille.h"

void	child_process_one(t_mini *list, char **env, t_pipe *pipes)
{
	int		fd1;
	char	**ps_path;
	char	*acs1;
	char	**args;

	if (list->infile == -1)
		ft_fail('f');
	ps_path = pathfinder(env);
	if (!ps_path)
		exit (1);
	acs1 = check_access(ps_path, list->cmd[0]);
	if (list->infile != -3)
		dup2(list->infile, 0);
	if (list->outfile != -3)
		dup2(list->outfile, 1);
	else
		dup2(pipes->fd[pipes->f0][1], 1);
	close(pipes->fd[pipes->f0][1]);
	close(pipes->fd[pipes->f1][0]);
	close(pipes->fd[pipes->f1][1]);
	execve(acs1, list->cmd, env);
	ft_fail('e');
}

void	child_process_two(t_mini *list, char **env, t_pipe *pipes, int check)
{
	char	**ps_path;
	char	*acs2;
	char	**args;

	ps_path = pathfinder(env);
	if (!ps_path)
		exit(1);
	acs2 = check_access(ps_path, list->cmd[0]);
	if (check == 0)
	{
		check++;
		dup2(pipes->fd[pipes->f0][0], 0);
	}
	else
		dup2(pipes->strin_main, 0);
	// if (check > 0)
	// {
	// 	printf("am here for strinn\n");
	// 	dup2(pipes->stdiin, 0);
	// }
	dup2(pipes->fd[pipes->f1][1], 1);
	close(pipes->fd[pipes->f0][0]);
	close(pipes->fd[pipes->f0][1]);
	close(pipes->fd[pipes->f1][0]);
	close(pipes->fd[pipes->f1][1]);
	execve(acs2, list->cmd, env);
	ft_fail('e');
}

void	last_child(t_mini *list, char **env, t_pipe *pipes)
{
	char	**ps_path;
	char	*acs2;
	char	**args;
	int		fd2;

	if (list->outfile == -1)
		ft_fail('f');
	ps_path = pathfinder(env);
	if (!ps_path)
		exit(1);
	acs2 = check_access(ps_path, list->cmd[0]);
	dup2(pipes->stdiin, 0);
	if (list->outfile != -3)
	{
		// printf("am here for duping pipe with outf\n");
		// fprintf(stderr, "outfile %d\n", pipes->fd[0][0 ]);
		// printf("%d\n", list->outfile);
		// printf("duping out with pipe\n");
		// printf("check%d\n", pipes->check);
		dup2(list->outfile, 1);
	}
	if(list->outfile != 1)
	{
		write(2, "am closed the file\n", 19);
		close(list->outfile);
	}
	close(pipes->fd[pipes->f0][0]);
	close(pipes->fd[pipes->f0][1]);
	close(pipes->fd[pipes->f1][0]);
	close(pipes->fd[pipes->f1][1]);
	execve(acs2, list->cmd, env);
	ft_fail('e');
}
