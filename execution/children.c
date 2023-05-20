/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 19:12:49 by werrahma          #+#    #+#             */
/*   Updated: 2023/05/20 21:16:00 by werrahma         ###   ########.fr       */
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

	// fd1 = open (av[0], O_RDONLY, 0777);
	// write(2,"here\n", 5);
	// exit (1);
	if (list->infile < 0)
		ft_fail('f');
	ps_path = pathfinder(env);
	if (!ps_path)
		exit (1);
	// args = ft_split(av[1], ' ');
	acs1 = check_access(ps_path, list->cmd[0]);
	if (list->infile != -3)
		dup2(fd1, 0);
	dup2(pipes->fd[0][1], 1);
	close(pipes->fd[0][0]);
	close(pipes->fd[0][1]);
	close(pipes->fd[1][0]);
	close(pipes->fd[1][1]);
	execve(acs1, list->cmd, env);
	ft_fail('e');
}

void	child_process_two(t_mini *list, char **env, t_pipe *pipes)
{
	char	**ps_path;
	char	*acs2;
	char	**args;

	ps_path = pathfinder(env);
	if (!ps_path)
		exit(1);
	// args = ft_split(av[i], ' ');
	acs2 = check_access(ps_path, list->cmd[0]);
	if (list->infile != -3)
		dup2(pipes->fd[pipes->f0][0], 0);
	if (list->outfile != -3)
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

	// fd2 = open (av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0777);
	// if (fd2 < 0)
	// 	ft_fail('f');
	ps_path = pathfinder(env);
	if (!ps_path)
		exit(1);
	// args = ft_split(av[ac - 2], ' ');
	printf("hrere\n");
	printf("infile ==  %d outfile == %d\n", list->infile, list->outfile);
	acs2 = check_access(ps_path, list->cmd[0]);
	printf("%s\n", acs2);
	if (list->infile != -3)
	{
		printf("am here for duping inf\n");
		dup2(pipes->fd[pipes->f0][0], 0);
	}
	if (list->outfile != -3)
	{
		printf("am here for duping outf\n");
		// dup2(list->outfile, 1);
	}
	close(pipes->fd[pipes->f0][0]);
	close(pipes->fd[pipes->f0][1]);
	close(pipes->fd[pipes->f1][0]);
	close(pipes->fd[pipes->f1][1]);
	if(list->outfile != -3)
	{
		printf("am closed the file\n");
		close(list->outfile);
	}
	execve(acs2, list->cmd, env);
	ft_fail('e');
}
