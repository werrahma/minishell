# include "../execution/minishell.h"

int main(int ac, char **av, char **env)
{
	char *line;
	t_tokens     *list;
	t_mini	*li;

	//while (1)
	//{
		line = readline("minishell$ ");
		list = lexer_split_cmdline(line);
		li = fill_last_list(list);
	//}
	
	printf("***%s\n", get_next_line(li->infile));
	//while(li)
	//{
		//printf(" %s   %d     %d\n", li->cmd[0], li->infile, li->outfile);
	//	li = li->next;
	//}
}