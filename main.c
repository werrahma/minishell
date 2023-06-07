#include "execution/minishell.h"

t_glo global;
int stx = 0;

int	syntax_checker(t_mini *list)
{
	while (list)
	{
		printf ("infile ==== %d\n", list->infile);
		if (list->infile == -1 || list->outfile == -1)
			return (0);
		list = list->next;
	}
	return (1);
}

// void handle_signal(int sig)
// {
// 	printf("\n");
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// }

int main(int ac, char **av, char **env)
{
    int i = 0;
    int j;
    char **hold;
	int	size_list;
	int	finale_exit;
    t_env   *list = NULL;
	t_tokens	*tokens;
    // t_env   *tmp = NULL;

    char *line;
	// t_tokens     *lst;
	t_mini	*li;
	t_pipe pipes;
	create_list(&list, env);
	fill_list(&list, env);
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
	// signal(SIGINT, handle_signal);
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			printf("exit\n");
			exit (1);
		}
		tokens = lexer_split_cmdline(line);
		do_expand_tokens(&tokens, list);
		li = fill_last_list(tokens);
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
		while(li)
		{
			// if(!check_agr(li->cmd, &list))
			// {
					// printf("hereaa\n");
				// if (!syntax_checker(li))
				// {
				// 	printf("for syntax\n");
				// 	break ;
				// }
				if (have_builtins(li->cmd) && ft_lstsize(li) == 1 && li->infile == -3 && li->outfile == -3)
				{
					printf("am in builtin\n");
					check_arg(li->cmd, &list);
				}
				else
				{
					// write(2, "hrere\n", 6);
					pipe(pipes.fd[0]);
					pipe(pipes.fd[1]);
					pipex(li, &pipes, &list);
				}
			// }
			// printf("f0 === %d,,,, f1 == %d", pipes.f0, pipes.f1);
			pipes.index++;
			li = li->next;
		}
		// while(waitpid())
		// while (wait(NULL) != -1)
		// 	continue;
		// printf("\ndup in the last time == %d\n",  stdin_main);
		dup2(stdin_main, pipes.strin_main);
		// dup2(stdout_main, pipes.stdouut);
		int i = 0;
		waitpid(pipes.pid[size_list - 1], &finale_exit, 0);
		while(i < size_list)
			waitpid(pipes.pid[i++], &stx, 0);
			// exit(1);
		// i = 0;
		// while(li->cmd[i])
		// 	printf("%s\n", li->cmd[i++]);
		if (line[0])
			add_history(line);
		free(line);
	}
	// exit (stx);

}