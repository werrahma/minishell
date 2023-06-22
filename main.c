/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 16:56:16 by yahamdan          #+#    #+#             */
/*   Updated: 2023/06/22 16:49:19 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution/minishell.h"

int	get_the_list(t_mini **li, t_env *list, char *line)
{
	extern int	g_status;
	t_tokens	*tokens;

	if (!line)
	{
		ft_putstr_fd("exit\n", 2);
		exit(g_status);
	}
	if (lexer_openqts(line, ft_strlen(line)))
	{
		free (line);
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
		g_status = 258;
		return (1);
	}
	tokens = lexer_split_cmdline(line);
	do_expand_tokens(&tokens, list);
	fill_last_list(tokens, list, li);
	return (0);
}

int	execution(t_mini *li, t_pipe *pipes, t_env **list)
{
	int	flag;

	flag = 0;
	while (li)
	{
		if (have_builtins(li->cmd) && pipes->size_list == 1
			&& li->infile == -3 && li->outfile == -3)
		{
			flag = 1;
			check_arg(li->cmd, list);
		}
		else
		{
			pipe(pipes->fd[0]);
			pipe(pipes->fd[1]);
			pipes_monitor(li, pipes, list);
		}
		pipes->index++;
		li = li->next;
	}
	return (flag);
}

int	monitor_main(int stdin_main, t_pipe *pipes, char *line, int flag)
{
	int	exit_status;
	int	i;

	i = 0;
	exit_status = g_status;
	dup2(stdin_main, pipes->strin_main);
	exit_status = g_status;
	if (!flag)
	{
		while (i < pipes->size_list)
			waitpid(pipes->pid[i++], &exit_status, 0);
		if (WIFEXITED(exit_status))
			g_status = WEXITSTATUS(exit_status);
		else if (WIFSIGNALED(exit_status))
			g_status = WTERMSIG(exit_status) + 128;
	}
	if (line[0])
		add_history(line);
	else
		g_status = 0;
	free(pipes->pid);
	free(line);
	unlink_hf();
	return (exit_status);
}

void	help_main(t_mini **li, t_env **list, t_pipe *pipes, char **env)
{
	*li = NULL;
	*list = NULL;
	pipes->stdin_m = dup(0);
	create_list(list, env);
	fill_list(list, env);
	if (!*list)
		create_env(list);
	pipes->strin_main = dup(0);
	signal(SIGQUIT, SIG_IGN);
	g_status = 0;
}

int	main(int ac, char **av, char **env)
{
	int		exit_status;
	t_env	*list;
	t_mini	*li;
	t_pipe	pipes;
	char	*line;

	(void)ac;
	(void)av;
	help_main(&li, &list, &pipes, env);
	while (1)
	{
		// signal(SIGINT, handle_signal);
		line = readline("minishell$ ");
		if (get_the_list(&li, list, line))
			continue ;
		init(&pipes, li);
		signal(SIGINT, handle_sig);
		pipes.flag = execution(li, &pipes, &list);
		exit_status = monitor_main(pipes.stdin_m, &pipes, line, pipes.flag);
		free_li(&li);
	}
	exit(exit_status);
}
