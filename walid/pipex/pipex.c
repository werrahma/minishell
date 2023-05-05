/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:42:32 by werrahma          #+#    #+#             */
/*   Updated: 2023/02/22 17:46:45 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	int	fd[2];
	int	id0;
	int	id1;

	if (ac != 5)
	{
		write(1, "bad arguments bye", 17);
		exit(1);
	}
	pipe(fd);
	id0 = fork();
	if (id0 == 0)
		child_process_one(av, env, fd);
	id1 = fork();
	if (id1 == 0)
		child_process_two(av, env, fd);
	else
	{
		close (fd[0]);
		close (fd[1]);
		waitpid(id0, 0, 0);
		waitpid(id1, 0, 0);
	}
	exit(0);
}
