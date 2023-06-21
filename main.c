/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 16:56:16 by yahamdan          #+#    #+#             */
/*   Updated: 2023/06/21 20:14:01 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution/minishell.h"

int		stx = 0;


// void	handle_signal(int sig)
// {
// 	(void) sig;
// 	stx = 1;
// 	printf("\n");
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// }

void	unlink_hf(void)
{
	char	*name;
	int	i;
	char 	*ii;

	i = 0;
	ii = ft_itoa(i);
	name = ft_strjoin("/tmp/here_doc", ii);
	while (!access(name, F_OK))
	{
		i++;
		unlink(name);
		free(name);
		free(ii);
		ii = ft_itoa(i);
		name = ft_strjoin("/tmp/here_doc", ii);
	}
	free(name);
	free(ii);
}

void	free_li(t_mini **li)
{
	t_mini *tmp;

	int i;
	while(*li)
	{
		tmp = (*li);
		i = 0;
		while ((*li)->cmd[i])
		{
			free((*li)->cmd[i++]);
		}
		free((*li)->cmd);
		(*li) = (*li)->next;
		free((tmp));
	}
}
int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	int size_list;
	int exit_status;
	t_env *list = NULL;
	t_tokens *tokens;

	char *line;
	t_mini *li = NULL;
	t_pipe pipes;
	t_mini *t;
	create_list(&list, env);
	fill_list(&list, env);
	if (!list)
		create_env(&list);
	pipes.env = env;
	pipes.strin_main = dup(0);
	int stdin_main = dup(0);
	signal(SIGQUIT, SIG_IGN);
	stx = 0;
	while (1)
	{
		// signal(SIGINT, handle_signal);
		line = readline("minishell$ ");
		if (!line)
		{
			ft_putstr_fd("exit\n", 2);
			exit(stx);
		}
		if(lexer_openqts(line, ft_strlen(line)))
		{
			free (line);
			ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
			stx = 258;
			continue;
		}
		tokens = lexer_split_cmdline(line);
		do_expand_tokens(&tokens, list);
		fill_last_list(tokens, list, &li);
		t = li;
		size_list = ft_lstsize(li);
		pipes.pid = tab_pid(li);
		pipes.index = 0;
		pipes.f0 = 0;
		pipes.f1 = 1;
		signal(SIGINT, handle_sig);
		int flag = 0;
		while (li)
		{
			if (have_builtins(li->cmd) && size_list == 1 && li->infile ==
				-3 && li->outfile == -3)
			{
				flag = 1;
				check_arg(li->cmd, &list);
			}
			else
			{
				pipe(pipes.fd[0]);
				pipe(pipes.fd[1]);
				pipes_monitor(li, &pipes, &list);
			}
			pipes.index++;
			li = li->next;
		}
		li = t;
		dup2(stdin_main, pipes.strin_main);
		int i = 0;
		exit_status = stx;
		if (!flag)
		{
			while (i < size_list)
				waitpid(pipes.pid[i++], &exit_status, 0);
			if (WIFEXITED(exit_status) && size_list == 1);
			else if (WIFEXITED(exit_status))
				stx = WEXITSTATUS(exit_status);
			else if (WIFSIGNALED(exit_status))
				stx = WTERMSIG(exit_status) + 128;
		}
		if (line[0])
			add_history(line);
		free(pipes.pid);
		free(line);
		unlink_hf();
		free_li(&li);
	}
	exit(exit_status);
}