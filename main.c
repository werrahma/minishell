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
		if (!line)
			break;
		// lst = lexer_split_cmdline(line);
		li = fill_last_list(lexer_split_cmdline(line));
		add_history(line);
		check_agr(li->cmd, &list);
		free(line);
	}
	// while(list)
	// {
	// 	printf("%s == ", list->key);
	// 	printf("%s\n", list->value);
	// 	list = list->next;
	// }

}