/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:42:32 by werrahma          #+#    #+#             */
/*   Updated: 2023/05/18 13:25:12 by werrahma         ###   ########.fr       */
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

// void	ft_main(int ac, char **av, char **env)
// {
// 	if (ac < 5)
// 		ft_fail('a');
// 	if (strcmp1(av[1], "here_doc") == 0)
// 	{
// 		here_doc(av, ac);
// 		__here_doc(ac, av, env);
// 		unlink(av[1]);
// 		exit (0);
// 	}
// }

int	pipex(int ac, char **av, char **env)
{
	t_pipe	pipes;
	int		id0;
	int		id2;

	pipes.f0 = 0;
	pipes.f1 = 1;
	// ft_main(ac, av, env);
	// int i = 0;
	// while(av[i])
	// 	printf("%s\n", av[i++]);
	// while(1);
	pipe(pipes.fd[0]);
	pipe(pipes.fd[1]);
	id0 = fork();
	if (id0 == 0)
		child_process_one(av, env, &pipes);
	help(av, env, ac, &pipes);
	id2 = fork();
	if (id2 == 0)
		last_child_child(ac, av, env, &pipes);
	close(pipes.fd[pipes.f0][0]);
	close(pipes.fd[pipes.f0][1]);
	close(pipes.fd[pipes.f1][0]);
	close(pipes.fd[pipes.f1][1]);
	while (wait(NULL) != -1)
		continue ;
	exit(0);
}
