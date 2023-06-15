#include "execution/minishell.h"

t_glo	global;
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

void handle_signal(int sig)
{
	stx = 1,
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void unlink_hf()
{
	char	*name;
	int 	i;
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

void	free_li(t_mini *li)
{
	t_mini *tmp;

	tmp = li;
	int i = 0;
	while(li)
	{
		tmp = li;
		li = li->next;
		while (li->cmd[i])
		{
			free(li->cmd[i++]);
		}
		i = 0;
		free(li->cmd);		
	}
}
int	main(int ac, char **av, char **env)
{
	int i = 0;
	int j;
	char **hold;
	int size_list;
	int exit_status;
	t_env *list = NULL;
	t_tokens *tokens;
	// t_env   *tmp = NULL;

	char *line;
	// t_tokens     *lst;
	t_mini *li = NULL;
	t_pipe pipes;
	t_mini *t = li;
	create_list(&list, env);
	fill_list(&list, env);
	// while(1);
	if (!list)
		create_env(&list);
	pipes.env = env;
	pipes.strin_main = dup(0);
	int stdout_main = dup(1);
	int stdin_main = dup(0);
	pipes.stdiin = dup(0);
	pipes.stdouut = dup(1);
	// printf("%d\n", pipes.stdiin);
	// pipe(pipes.fd[1]);
	// exit(1);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		signal(SIGINT, handle_signal);
		line = readline("minishell$ ");
		if (!line)
		{
			printf("exit\n");
			exit(1);
		}
		if(lexer_openqts(line, ft_strlen(line)))
		{
			ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
			stx = 1;
			continue;
		}
		// system("leaks minishell");
		tokens = lexer_split_cmdline(line);
		do_expand_tokens(&tokens, list);
		//write(2, "gg\n", 3);
		li = fill_last_list(tokens, list);
		//puts("fffff");
		size_list = ft_lstsize(li);
		pipes.pid = tab_pid(li);
		pipes.index = 0;
		// while(li)
		// {
		// 	printf("jhsd\n");
		// 	li = li->next;
		// }
		// exit(1);
		// lst = lexer_split_cmdline(line);
		//li = fill_last_list(lexer_split_cmdline(line));
		//printf("***********\n");
		pipes.f0 = 0;
		pipes.f1 = 1;
		while (li)
		{
			// if(!check_agr(li->cmd, &list))
			// {
			// printf("hereaa\n");
			// if (!syntax_checker(li))
			// {
			// 	printf("for syntax\n");
			// 	break ;
			// }
			if (have_builtins(li->cmd) && size_list == 1 && li->infile ==
				-3 && li->outfile == -3)
			{
				// printf("am in builtin\n");
				check_arg(li->cmd, &list);
				// printf("stx === %d\n", stx);
			}
			else
			{
				// write(2, "hrere\n", 6);
				pipe(pipes.fd[0]);
				pipe(pipes.fd[1]);
				pipes_monitor(li, &pipes, &list);
			}
			// }
			// printf("f0 === %d,,,, f1 == %d", pipes.f0, pipes.f1);
			pipes.index++;
			li = li->next;
		}
		li = t;
		// while(waitpid())
		// while (wait(NULL) != -1)
		// 	continue ;
		// printf("\ndup in the last time == %d\n",  stdin_main);
		dup2(stdin_main, pipes.strin_main);
		// dup2(stdout_main, pipes.stdouut);
		int i = 0;
		// waitpid(pipes.pid[size_list - 1], &exit_status, 0);
		while (i < size_list)
			waitpid(pipes.pid[i++], &exit_status, 0);
		// printf("status == %d\n", stx);
		if (WIFEXITED(exit_status))
			stx = WEXITSTATUS(exit_status);
		// exit(1);
		// i = 0;
		// while(li->cmd[i])
		// 	printf("%s\n", li->cmd[i++]);
		if (line[0])
			add_history(line);
		free(line);
		free_li(li);
		unlink_hf();
		system("leaks minishell");
		// system("leaks minishell");
	}
	exit(exit_status);
}