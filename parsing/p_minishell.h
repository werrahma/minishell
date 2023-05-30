#ifndef P_MINISHELL_H
#define P_MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <limits.h>
# include <strings.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
#include "../execution/minishell.h"
#include "../execution/libft/libft.h"

typedef	struct s_tokens
{
	int		type;
	char	*cont;
	struct s_tokens	*next;
	struct s_tokens	*perv;
}	t_tokens;


typedef struct s_mini
{
	char	**cmd;
	int		infile;
	int		outfile;
	struct s_mini *next;
}	t_mini;


t_tokens	*lexer_split_cmdline(char *line);
t_mini  *fill_last_list(t_tokens *token);
t_mini	*ft_lstlastl(t_mini *lst);
void	ft_lstadd_backl(t_mini **lst, t_mini *new);
// parsinghelperf

t_tokens	*ft_lstnewp(char *content);
size_t		ft_strlen(const char *s);
t_tokens	*ft_lstlastp(t_tokens *lst);
char		*ft_strdup(const char *s1);
char		*ft_chrjoin(char *dst, char c);
void		*ft_calloc(size_t count, size_t size);
void		ft_lstadd_backp(t_tokens **lst, t_tokens *new);
int			lexer_openqts(char	*line, int indx);
char	*get_next_line(int fd);
int		ft_strcmp(const char *s1, const char *s2);
void    open_herfiles(t_tokens *tokens);
void    expand_tokens(t_tokens *token, t_env *env);

# define INFILE 0
# define OUTFILE 1
# define PIPE 2
# define HEREDOC 3
# define LIMETER 4
# define ARG 5
# define INPUT 6
# define OUTPUT 7
# define APPEND 8

// enum type {
// 	infile,
// 	outfile,
// }

#endif