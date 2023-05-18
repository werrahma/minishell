/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 22:22:57 by werrahma          #+#    #+#             */
/*   Updated: 2023/05/18 19:28:18 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "../execution/libft/libft.h"
# include "../execution/minishell.h"
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_pipe
{
	int	fd[2][2];
	int	f0;
	int	f1;
}				t_pipe;

void	child_process_one(t_mini *list, char **env, t_pipe *pipes);
char	*check_access(char **ps_path, char *av);
char	**pathfinder(char **env);
void	child_process_two(t_mini *list, char **env, t_pipe *pipes);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s1);
// char	*ft_strjoin(char *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *ar);
void	last_child(int infile, char **env, t_pipe *pipes);
// int		here_doc(char **av, int ac);
// char	*get_next_line(int fd);
int		ft_strcmp(const char *s1, const char *s2);
// void	h_c_child_process_one(char **av, char **env, t_pipe *pipes);
// void	h_c_child_process_two(char **av, char **env, t_pipe *pipes, int i);
// void	h_c_last_child_child(int ac, char **av, char **env, t_pipe *pipes);
// void	__here_doc(int ac, char **av, char **env);
void	swap(int *a, int *b);
int		strcmp1(char *s1, char *s2);
void	multiple_pipe(t_mini *list, char **env, t_pipe *pipes);
void	h_d_help(char **av, char **env, int ac, t_pipe *pipes);
void	ft_fail(char av);
int		size_lim(char *str, char *av);
char	*get_strjoin(char *s1, char *s2);
int		ft_checker(int ac, char *av);
// int	pipex(int ac, char **av, char **env);

#endif