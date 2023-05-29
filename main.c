#include "execution/minishell.h"


int main(int ac, char **av, char **env)
{
    int i = 0;
    int j;
    char **hold;
    t_env   *list = NULL;
	t_tokens	*tokens;
    // t_env   *tmp = NULL;

    char *line;
	// t_tokens     *lst;
	t_mini	*li;
	t_pipe pipes;

	create_list(&list, env);
	fill_list(&list, env);
	pipes.env = env;
	// pipes.stdiin = dup(0);
	// pipes.stdoout = dup(1);
	// pipes.f0 = 0;
	// pipes.f1 = 1;
	pipes.strin_main = dup(0);
	int strout_main = dup(1);
	int stdin_main = dup(0);
	pipes.stdiin = dup(0);
	pipes.stdouut = dup(1);
	// printf("%d\n", pipes.stdiin);
				// pipe(pipes.fd[1]);
	// exit(1);
	while (1)
	{
		line = readline("minishell$ ");
		tokens = lexer_split_cmdline(line);
		do_expand_tokens(&tokens, list);
		li = fill_last_list(tokens);
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
		// dup2(stdin_main, 0);
		// dup2(strout_main, 1);
		while(li)
		{
			// if(!check_agr(li->cmd, &list))
			// {
					// printf("hereaa\n");
				if (have_builtins(li->cmd) && ft_lstsize(li) == 1)
				{
					
					check_arg(li->cmd, &list);
				}
				else
				{
					write(2, "hrere\n", 6);
					pipe(pipes.fd[0]);
					pipe(pipes.fd[1]);
					pipex(li, &pipes, &list);
				}
			// }
			// printf("f0 === %d,,,, f1 == %d", pipes.f0, pipes.f1);
			li = li->next;
		}
			// exit(1);
		// i = 0;
		// while(li->cmd[i])
		// 	printf("%s\n", li->cmd[i++]);
		add_history(line);
		free(line);
	}
	// while(list)
	// {
	// 	printf("%s == ", list->key);
	// 	printf("%s\n", list->value);
	// 	list = list->next;


	
	// }

}