/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahamdan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 16:56:16 by yahamdan          #+#    #+#             */
/*   Updated: 2023/06/21 18:36:34 by yahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution/minishell.h"

int		stx = 0;

int	syntax_checker(t_mini *list)
{
	while (list)
	{
		printf("infile ==== %d\n", list->infile);
		if (list->infile == -1 || list->outfile == -1)
			return (0);
		list = list->next;
	}
	return (1);
}

void	handle_signal(int sig)
{
	(void) sig;
	stx = 1;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

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
	pipes.stdiin = dup(0);
	pipes.stdouut = dup(1);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		signal(SIGINT, handle_signal);
		line = readline("minishell$ ");
		if (!line)
		{
			printf("exit\n");
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
		while (li)
		{
			if (have_builtins(li->cmd) && size_list == 1 && li->infile ==
				-3 && li->outfile == -3)
			{
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
		while (i < size_list)
			waitpid(pipes.pid[i++], &exit_status, 0);
		if (WIFEXITED(exit_status) && size_list > 1)
			stx = WEXITSTATUS(exit_status);
		if (line[0])
			add_history(line);
		free(pipes.pid);
		free(line);
		unlink_hf();
		free_li(&li);
	}
	exit(exit_status);
}