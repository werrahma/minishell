/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahamdan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 19:12:49 by werrahma          #+#    #+#             */
/*   Updated: 2023/06/21 16:37:13 by yahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execve_failure_task(t_mini *list, t_pipe *pipes)
{
	int	i;

	i = 0;
	our_free(pipes->env);
	while (list->cmd[i])
	{
		printf("minishell: %s No such file or directory\n",
			list->cmd[i++]);
	}
	exit(127);
}

void	exuc_cmd(t_pipe *pipes, t_env *env, t_mini *list, char *acs)
{
	pipes->env = get_env(env);
	execve(acs, list->cmd, pipes->env);
	execve_failure_task(list, pipes);
}

void	first_child(t_mini *list, t_pipe *pipes, t_env **env)
{
	char	**ps_path;
	char	*acs;
	int		flag;

	flag = 0;
	acs = NULL;
	if (list->infile == -1 || list->outfile == -1)
		exit(1);
	check_open(list);
	ps_path = pathfinder(*env);
	if (have_builtins(list->cmd))
		flag = 1;
	else if (!ps_path && list->cmd[0][0] != '/')
		child_failure(list, -1, pipes, env);
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
	child_failure(list, flag, pipes, env);
	exuc_cmd(pipes, *env, list, acs);
}

void	second_child(t_mini *list, t_pipe *pipes, t_env **env)
{
	char	**ps_path;
	char	*acs;
	int		flag;

	flag = 0;
	acs = NULL;
	ps_path = pathfinder(*env);
	if (have_builtins(list->cmd))
		flag = 1;
	else if (!ps_path && list->cmd[0][0] != '/')
		child_failure(list, -1, pipes, env);
	else if (list->cmd[0])
		acs = check_access(ps_path, list->cmd[0]);
	if (!acs && !flag)
		exit(127);
	dup2(pipes->strin_main, 0);
	dup2(pipes->fd[pipes->f1][1], 1);
	child_failure(list, flag, pipes, env);
	exuc_cmd(pipes, *env, list, acs);
}

void	last_child(t_mini *list, t_pipe *pipes, t_env **env)
{
	char	**ps_path;
	char	*acs;
	int		flag;
	int		i;

	flag = 0;
	i = 0;
	acs = NULL;
	if (list->outfile == -1 || list->infile == -1)
		exit(1);
	check_open(list);
	ps_path = pathfinder(*env);
	if (have_builtins(list->cmd))
		flag = 1;
	else if (!ps_path && list->cmd[0] && list->cmd[0][0] != '/')
		child_failure(list, -1, pipes, env);
	else if (list->cmd[0])
		acs = check_access(ps_path, list->cmd[0]);
	if (!acs && !flag)
		exit(127);
	dup2(pipes->strin_main, 0);
	if (list->outfile != -3)
		dup2(list->outfile, 1);
	if (list->outfile != 1)
		close(list->outfile);
	child_failure(list, flag, pipes, env);
	exuc_cmd(pipes, *env, list, acs);
}
