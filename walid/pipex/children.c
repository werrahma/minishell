/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 19:12:49 by werrahma          #+#    #+#             */
/*   Updated: 2023/02/22 17:25:35 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process_one(char **av, char **env, int *fd)
{
	int		fd1;
	char	**ps_path;
	char	*acs1;
	char	**args;

	fd1 = open (av[1], O_RDONLY, 0777);
	if (fd1 < 0)
	{
		write(1, "open failed\n", 13);
		exit (1);
	}
	ps_path = pathfinder(env);
	if (!ps_path)
		exit (1);
	args = ft_split(av[2], ' ');
	acs1 = check_access(ps_path, args[0]);
	dup2(fd1, 0);
	dup2(fd[1], 1);
	close(fd[0]);
	execve(acs1, args, env);
	write(2, "\nexecve->fail\n", 14);
	exit(1);
}

void	child_process_two(char **av, char **env, int *fd)
{
	int		fd2;
	char	**ps_path;
	char	*acs2;
	char	**args;

	fd2 = open (av[4], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd2 < 0)
	{
		write(1, "open failed\n", 13);
		exit (1);
	}
	ps_path = pathfinder(env);
	if (!ps_path)
		exit(1);
	args = ft_split(av[3], ' ');
	acs2 = check_access(ps_path, args[0]);
	dup2(fd[0], 0);
	dup2(fd2, 1);
	close(fd[1]);
	execve(acs2, args, env);
	write(2, "\nexecve->fail\n", 14);
	exit(1);
}
