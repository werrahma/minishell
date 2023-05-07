#include "minishell.h"

int main(int ac, char **av, char **env)
{
    char *line;
    t_tokens     *list;

   //line = "<h | yassine >> .    mm mm  ls | ";
    line = readline("minishell > ");
    list = lexer_split_cmdline(line);
    // printf("prev = %s | main = %s\n",list->cont , list->cont);
    //   list = list->next;
    while(list)
    {
      printf("main = %s\n", list->cont);
      list = list->next;
    }

}