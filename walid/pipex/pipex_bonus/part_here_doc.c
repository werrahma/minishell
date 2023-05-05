/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 15:36:53 by werrahma          #+#    #+#             */
/*   Updated: 2023/02/22 17:21:15 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	h_c_child_process_one(char **av, char **env, t_pipe *pipes)
{
	int		fd1;
	char	**ps_path;
	char	*acs1;
	char	**args;

	fd1 = open (av[1], O_RDWR, 0777);
	if (fd1 < 0)
		ft_fail('f');
	ps_path = pathfinder(env);
	if (!ps_path)
		exit (1);
	args = ft_split(av[3], ' ');
	acs1 = check_access(ps_path, args[0]);
	dup2(fd1, 0);
	dup2(pipes->fd[0][1], 1);
	close(pipes->fd[0][0]);
	close(pipes->fd[0][1]);
	close(pipes->fd[1][0]);
	close(pipes->fd[1][1]);
	close(fd1);
	execve(acs1, args, env);
	ft_fail('e');
}

void	h_c_child_process_two(char **av, char **env, t_pipe *pipes, int i)
{
	char	**ps_path;
	char	*acs2;
	char	**args;

	ps_path = pathfinder(env);
	if (!ps_path)
		exit(1);
	args = ft_split(av[i], ' ');
	acs2 = check_access(ps_path, args[0]);
	dup2(pipes->fd[pipes->f0][0], 0);
	dup2(pipes->fd[pipes->f1][1], 1);
	close(pipes->fd[pipes->f0][0]);
	close(pipes->fd[pipes->f0][1]);
	close(pipes->fd[pipes->f1][0]);
	close(pipes->fd[pipes->f1][1]);
	execve(acs2, args, env);
	write(2, "\nexecve->fail\n", 14);
	exit(1);
}

void	h_c_last_child_child(int ac, char **av, char **env, t_pipe *pipes)
{
	char	**ps_path;
	char	*acs2;
	char	**args;
	int		fd2;

	fd2 = open (av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd2 < 0)
	{
		write(1, "open failed 2 \n", 16);
		exit (1);
	}
	ps_path = pathfinder(env);
	if (!ps_path)
		exit(1);
	args = ft_split(av[ac - 2], ' ');
	acs2 = check_access(ps_path, args[0]);
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

void	__here_doc(int ac, char **av, char **env)
{
	t_pipe	pipes;
	int		id0;
	int		id2;

	pipes.f0 = 0;
	pipes.f1 = 1;
	pipe(pipes.fd[0]);
	pipe(pipes.fd[1]);
	id0 = fork();
	if (id0 == 0)
		h_c_child_process_one(av, env, &pipes);
	h_d_help(av, env, ac, &pipes);
	id2 = fork();
	if (id2 == 0)
		h_c_last_child_child(ac, av, env, &pipes);
	close(pipes.fd[pipes.f0][0]);
	close(pipes.fd[pipes.f0][1]);
	close(pipes.fd[pipes.f1][0]);
	close(pipes.fd[pipes.f1][1]);
	while (wait(NULL) != -1)
		continue ;
}
