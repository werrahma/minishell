#include "execution/minishell.h"

int main(int ac, char **av, char **env)
{
    int i = 0;
    int j;
    char **hold;
    t_env   *list = NULL;
    // t_env   *tmp = NULL;

    char *line;
	t_tokens     *lst;
	t_mini	*li;

	while (1)
	{
		line = readline("minishell$ ");
		lst = lexer_split_cmdline(line);
		li = fill_last_list(lst);
	}
	create_list(&list, env);
	fill_list(&list, env);
	check_agr(av, &list);
	while(list)
	{
		printf("%s == ", list->key);
		printf("%s\n", list->value);
		list = list->next;
	}

}