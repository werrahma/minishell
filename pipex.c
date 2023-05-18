/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 13:15:07 by werrahma          #+#    #+#             */
/*   Updated: 2023/05/18 19:27:08 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./execution/minishell.h"

void	pipex(t_mini *list, char **env)
{
	t_pipe	pipes;
	int		chld_o;
	int		chld_t;

	pipe(pipes.fd[0]);
	pipe(pipes.fd[1]);
	chld_o = fork();
	if (chld_o == 0)
		child_process_one(list, env, &pipes);
	multiple_pipe(list, env, &pipes);
	chld_t = fork();
	if (chld_t == 0)
		last_child(list, env, &pipes);
	close(pipes.fd[pipes.f0][0]);
	close(pipes.fd[pipes.f0][1]);
	close(pipes.fd[pipes.f0][0]);
	close(pipes.fd[pipes.f0][1]);
	while (wait(NULL) != 1)
	exit(0);
}