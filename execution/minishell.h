#ifndef MINISHELL_H
# define MINISHELL_H

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


typedef struct s_list
{
	char **str;
}				t_list;

typedef struct s_env
{
	char	*key;
	char	*value;
	int		data;
	struct s_env  *next;
}				t_env;

typedef struct s_pipe
{
	int	fd[2][2];
	int	stdiin;
	int	stdouut;
	int strin_main;
	char **env;
	int check;
	int	f0;
	int	f1;
}				t_pipe;

// #include "../parsing/p_minishell.h"
# include "libft/libft.h"
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
// # include "../pipex_bonus/pipex.h"

// #include <readline/readline.h>
// #include <readline/history.h>

void	create_list(t_env **list, char **env);
void	ft_lstadd_back(t_env **lst, t_env *new);
t_env	*ft_lstnew(int content);
t_env	*ft_lstlast(t_env *lst);
// void	ft_cd(t_env *env);
int		ft_strcmp(const char *s1, const char *s2);
void	pwd(void);
void	ft_env(t_env *env);
int		echo(char **str);
void	ft_cd(t_env *env, char *file);
void	unset(t_env **env, char **remove);
int		my_exit(char **av);
int		str_len(char **av);
void	my_export(t_env **env, char **av);
int		cmp_env(char *str1, char *str2);
void	sort_list(t_env **env);
void	fill_list(t_env **list, char **env);
int		check_arg(char **av, t_env **env);

void	child_process_one(t_mini *list, t_pipe *pipes, t_env **env);
void	child_process_two(t_mini *list, t_pipe *pipes, t_env **env);
void	last_child(t_mini *list, t_pipe *pipes, t_env **env);
char	*check_access(char **ps_path, char *av);
char	**pathfinder(char **env);
void	swap(int *a, int *b);
void	multiple_pipe(t_mini *list, t_env **env, t_pipe *pipes);
void	ft_fail(char av);
int		size_lim(char *str, char *av);
int		ft_checker(int ac, char *av);
void	pipex(t_mini *list, t_pipe *pipes, t_env **env);

// ***** parsing 
// typedef	struct s_tokens
// {
// 	int		type;
// 	char	*cont;
// 	struct s_tokens	*next;
// 	struct s_tokens	*perv;
// }	t_tokens;


// typedef struct s_mini
// {
// 	char	**cmd;
// 	int		infile;
// 	int		outfile;
// 	struct s_mini *next;
// }	t_mini;

void    stxe(t_tokens *to);
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
char		*get_next_line(int fd);
int			ft_strcmp(const char *s1, const char *s2);
void    	open_herfiles(t_tokens *tokens);
void    	do_expand_tokens(t_tokens **tokens, t_env *env);
int			have_builtins(char **cmd);
int			ft_lstsize(t_mini *lst);

# define INFILE 0
# define OUTFILE 1
# define PIPE 2
# define HEREDOC 3
# define LIMETER 4
# define ARG 5
# define INPUT 6
# define OUTPUT 7
# define APPEND 8


#endif