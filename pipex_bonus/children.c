/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 19:12:49 by werrahma          #+#    #+#             */
/*   Updated: 2023/05/19 18:46:36 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
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
	dup2(fd1, 0);
	dup2(pipes->fd[0][1], 1);
	close(pipes->fd[0][0]);
	close(pipes->fd[0][1]);
	close(pipes->fd[1][0]);
	close(pipes->fd[1][1]);
	execve(acs1, args, env);
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
	dup2(pipes->fd[pipes->f0][0], 0);
	dup2(pipes->fd[pipes->f1][1], 1);
	close(pipes->fd[pipes->f0][0]);
	close(pipes->fd[pipes->f0][1]);
	close(pipes->fd[pipes->f1][0]);
	close(pipes->fd[pipes->f1][1]);
	execve(acs2, args, env);
	ft_fail('e');
}

void	last_child(t_mini *list, char **env, t_pipe *pipes)
{
	char	**ps_path;
	char	*acs2;
	char	**args;
	int		fd2;

	// fd2 = open (av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd2 < 0)
		ft_fail('f');
	ps_path = pathfinder(env);
	if (!ps_path)
		exit(1);
	// args = ft_split(av[ac - 2], ' ');
	acs2 = check_access(ps_path, list->cmd[0]);
	dup2(pipes->fd[pipes->f0][0], 0);
	dup2(fd2, 1);
	close(pipes->fd[pipes->f0][0]);
	close(pipes->fd[pipes->f0][1]);
	close(pipes->fd[pipes->f1][0]);
	close(pipes->fd[pipes->f1][1]);
	close(fd2);
	execve(acs2, args, env);
	ft_fail('e');
}
