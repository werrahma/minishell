/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 19:12:49 by werrahma          #+#    #+#             */
/*   Updated: 2023/06/05 13:23:47 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// # include "../execution/minishille.h"

void	child_process_one(t_mini *list, t_pipe *pipes, t_env **env)
{
	int		fd1;
	char	**ps_path;
	char	*acs1;
	char	**args;
	int		flag;

	flag = 0;
	// printf("infile ===  %d\n",list->infile);
	if (list->infile == -1)
		ft_fail('f');
	ps_path = pathfinder(pipes->env);
	if (!ps_path)
		exit (1);
	if (list->cmd[0])
		acs1 = check_access(ps_path, list->cmd[0]);
	if (list->infile != -3)
		dup2(list->infile, 0);
	if (list->outfile != -3)
		dup2(list->outfile, 1);
	else
		dup2(pipes->fd[pipes->f0][1], 1);
	if (have_builtins(list->cmd))
	{
		flag = 1;
		check_arg(list->cmd, env);
	}
	close(pipes->fd[pipes->f0][1]);
	close(pipes->fd[pipes->f0][0]);
	close(pipes->fd[pipes->f1][0]);
	close(pipes->fd[pipes->f1][1]);
	if (flag == 1 || !list->cmd[0])
		exit (0);
	execve(acs1, list->cmd, pipes->env);
	ft_fail('e');
}

void	child_process_two(t_mini *list, t_pipe *pipes, t_env **env)
{
	char	**ps_path;
	char	*acs2;
	char	**args;
	int		flag;

	flag = 0;
	ps_path = pathfinder(pipes->env);
	if (!ps_path)
	{
		printf("am failed\n"
		);
		exit(1);
	}
	if (list->cmd[0])
		acs2 = check_access(ps_path, list->cmd[0]);
	dup2(pipes->strin_main, 0);
	dup2(pipes->fd[pipes->f1][1], 1);
	if (have_builtins(list->cmd))
	{
		flag = 1;
		check_arg(list->cmd, env);
	}
	close(pipes->fd[pipes->f0][0]);
	close(pipes->fd[pipes->f0][1]);
	close(pipes->fd[pipes->f1][0]);
	close(pipes->fd[pipes->f1][1]);
	if (flag == 1 || !list->cmd[0])
		exit (0);
	execve(acs2, list->cmd, pipes->env);
	ft_fail('e');
}

void	last_child(t_mini *list, t_pipe *pipes, t_env **env)
{
	char	**ps_path;
	char	*acs2;
	char	**args;
	int		fd2;
	int		flag;

	flag = 0;
	// printf("out === %d\n", list->outfile);
	if (list->outfile == -1)
		ft_fail('f');
	ps_path = pathfinder(pipes->env);
	if (!ps_path)
		exit(1);
	if (list->cmd[0])
		acs2 = check_access(ps_path, list->cmd[0]);
	dup2(pipes->strin_main, 0);
	if (list->outfile != -3)
	{
		dup2(list->outfile, 1);
	}
	if(list->outfile != 1)
	{
		// write(2, "am closed the file\n", 19);
		close(list->outfile);
	}
	if (have_builtins(list->cmd))
	{
		flag = 1;
		check_arg(list->cmd, env);
	}
	close(pipes->fd[pipes->f0][0]);
	close(pipes->fd[pipes->f0][1]);
	close(pipes->fd[pipes->f1][0]);
	close(pipes->fd[pipes->f1][1]);
	if (flag == 1 || !list->cmd[0])
		exit (0);
	execve(acs2, list->cmd, pipes->env);
	ft_fail('e');
}
