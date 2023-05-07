#ifndef MINISHELL_H
#define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <limits.h>
# include <strings.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_lexer
{
	int   *i;
	char c; 
	char *content;
}      t_lexer;

typedef	struct s_tokens
{
	int		type;
	char	*cont;
	struct s_tokens	*next;
	struct s_tokens	*perv;
}	t_tokens;

//t_lexer *lexer_init(char *line);


t_tokens	*lexer_split_cmdline(char *line);
// parsinghelperf

t_tokens	*ft_lstnew(char *content);
size_t	ft_strlen(const char *s);
t_tokens	*ft_lstlast(t_tokens *lst);
char	*ft_strdup(const char *s1);
char	*ft_chrjoin(char *dst, char c);
void	*ft_calloc(size_t count, size_t size);
void	ft_lstadd_back(t_tokens **lst, t_tokens *new);


// typedef struct mini
// {
// 	char **cmd;
	char af
// 	int infile;
// 	int outfile;

// };
 

#endif