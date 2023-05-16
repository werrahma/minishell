#include "execution/minishell.h"

int main()
{
    char *line;

    int p[2];
    dup2(p[0], 0);
    while (1)
	{
		line = readline("minishell$ ");
        printf("%s\n",line);
		// lst = lexer_split_cmdline(line);
	}
}