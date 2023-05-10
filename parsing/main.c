#include "minishell.h"

int main(int ac, char **av, char **env)
{
	char *line;
	t_tokens     *list;
	t_mini	*li;

	//line = "<h | yassine >> .    mm mm  ls | ";
	line = readline("minishell > ");
	list = lexer_split_cmdline(line);
	li = fill_last_list(list);
	while(li)
	{
		//printf(" %s   %d     %d\n", li->cmd[0], li->infile, li->outfile);
		li = li->next;
	}
	// list = lexer_split_cmdline(line);
	// printf("prev = %s | main = %s\n",list->cont , list->cont);
	// list = list->next;
	// int i = 0;
	// while(li)
	// {
	// 	i = 0;
	// 	while (li->cmd)
	// 	{
	// 		printf("cmd == %s", li->cmd[i]);
	// 		i++;
	// 	}
	// 	printf(" in ==  %d  | out == %d \n", li->infile , li->outfile);
	// 	// li = li->next;
	// }

}