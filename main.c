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

	create_list(&list, env);
	fill_list(&list, env);
	while (1)
	{
		line = readline("minishell$ ");
		// lst = lexer_split_cmdline(line);
		li = fill_last_list(lexer_split_cmdline(line));
		// while(li)
		// {
		// 	printf("jhsd\n");
		// 	li = li->next;
		// }
		// exit(1);
		while(li)
		{
			printf("here\n");
			// if(!check_agr(li->cmd, &list))
				pipex(li, env);
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