#include "minishell.h"

int main(int ac, char **av, char **env)
{
    char *line;
    t_tokens     *list;

    line = "yassine  > .";
    list = lexer_split_cmdline(line);
    while(list)
    {
        printf("%s\n", list->cont);
        list = list->next;
    }
}