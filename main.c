#include "execution/minishell.h"


int main(int ac, char **av, char **env)
{
    int i = 0;
    int j;
    char **hold;
    t_env   *list = NULL;
    // t_env   *tmp = NULL;

    char *line;
	// t_tokens     *lst;
	t_mini	*li;
	t_pipe pipes;

	create_list(&list, env);
	fill_list(&list, env);
	pipes.f0 = 0;
	pipes.f1 = 1;
	// exit(1);
	while (1)
	{
		line = readline("minishell$ ");
		// lst = lexer_split_cmdline(line);
		li = fill_last_list(lexer_split_cmdline(line));
		while(li)
		{
			if(!check_agr(li->cmd, &list))
				pipex(li, env, &pipes);
			// printf("f0 === %d,,,, f1 == %d", pipes.f0, pipes.f1);
			// exit(1);
			li = li->next;
		}
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