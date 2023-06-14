/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 19:12:49 by werrahma          #+#    #+#             */
/*   Updated: 2023/06/14 12:03:34 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// # include "../execution/minishille.h"

void	first_child(t_mini *list, t_pipe *pipes, t_env **env)
{
	int		fd1;
	char	**ps_path;
	char	*acs;
	char	**args;
	int		flag;
	int		i;

	flag = 0;
	i = 0;
	if (list->infile == -1 || list->outfile == -1)
		exit(1);
	ps_path = pathfinder(*env);
	if (!ps_path && list->cmd[0][0] != '/')
	{
		while (list->cmd[i])
			printf("minishell: %s No such file or directory\n",
					list->cmd[i++]);
		exit(1);
	}
	if (have_builtins(list->cmd))
		flag = 1;
	else if (list->cmd[0])
		acs = check_access(ps_path, list->cmd[0]);
	if (!acs && !flag)
		exit(127);
	if (list->infile != -3)
		dup2(list->infile, 0);
	if (list->outfile != -3)
		dup2(list->outfile, 1);
	else
		dup2(pipes->fd[pipes->f0][1], 1);
	if (flag == 1)
		check_arg(list->cmd, env);
	close(pipes->fd[pipes->f0][1]);
	close(pipes->fd[pipes->f0][0]);
	close(pipes->fd[pipes->f1][0]);
	close(pipes->fd[pipes->f1][1]);
	if (flag == 1 || !list->cmd[0])
		exit(0);
	execve(acs, list->cmd, get_env(*env));
	exit(127);
}

void	second_child(t_mini *list, t_pipe *pipes, t_env **env)
{
	char	**ps_path;
	char	*acs;
	char	**args;
	int		flag;
	int		i;

	flag = 0;
	i = 0;
	ps_path = pathfinder(*env);
	if (!ps_path && list->cmd[0][0] != '/')
	{
		while (list->cmd[i])
			printf("miinishell: %s No such file or directory\n",
					list->cmd[i++]);
		exit(1);
	}
	if (have_builtins(list->cmd))
		flag = 1;
	else if (list->cmd[0])
		acs = check_access(ps_path, list->cmd[0]);
	if (!acs && !flag)
		exit(127);
	dup2(pipes->strin_main, 0);
	dup2(pipes->fd[pipes->f1][1], 1);
	if (flag == 1)
		check_arg(list->cmd, env);
	close(pipes->fd[pipes->f0][0]);
	close(pipes->fd[pipes->f0][1]);
	close(pipes->fd[pipes->f1][0]);
	close(pipes->fd[pipes->f1][1]);
	if (flag == 1 || !list->cmd[0])
		exit(0);
	execve(acs, list->cmd, get_env(*env));
	exit(127);
}

void	last_child(t_mini *list, t_pipe *pipes, t_env **env)
{
	char	**ps_path;
	char	*acs;
	char	**args;
	int		fd2;
	int		flag;
	int		i;

	flag = 0;
	i = 0;
	if (list->outfile == -1 || list->infile == -1)
		exit(1);
	ps_path = pathfinder(*env);
	if (!ps_path && list->cmd[0] && list->cmd[0][0] != '/')
	{
		while (list->cmd[i])
			printf("miinishell: %s No such file or directory\n",
					list->cmd[i++]);
		exit(1);
	}
	if (have_builtins(list->cmd))
		flag = 1;
	else if (list->cmd[0])
		acs = check_access(ps_path, list->cmd[0]);
	if (!acs && !flag)
		exit(127);
	dup2(pipes->strin_main, 0);
	if (list->outfile != -3)
		dup2(list->outfile, 1);
	if (list->outfile != 1)
	{
		// write(2, "am closed the file\n", 19);
		close(list->outfile);
	}
	if (flag == 1)
		check_arg(list->cmd, env);
	close(pipes->fd[pipes->f0][0]);
	close(pipes->fd[pipes->f0][1]);
	close(pipes->fd[pipes->f1][0]);
	close(pipes->fd[pipes->f1][1]);
	if (flag == 1 || !list->cmd[0])
		exit(0);
	execve(acs, list->cmd, get_env(*env));
	exit(127);
}
