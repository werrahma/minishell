/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <werrahma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 19:12:49 by werrahma          #+#    #+#             */
/*   Updated: 2023/05/23 23:26:29 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// # include "../execution/minishille.h"

void	child_process_one(t_mini *list, char **env, t_pipe *pipes)
{
	int		fd1;
	char	**ps_path;
	char	*acs1;
	char	**args;

	// fd1 = open (av[0], O_RDONLY, 0777);
	// write(2,"here\n", 5);
	// exit (1);
	if (list->infile == -1)
		ft_fail('f');
	ps_path = pathfinder(env);
	if (!ps_path)
		exit (1);
	// args = ft_split(av[1], ' ');
	acs1 = check_access(ps_path, list->cmd[0]);
	if (list->infile != -3)
		dup2(list->infile, 0);
	if (list->outfile != -3)
	{
		// printf("khra am duping 1 with outfile\n");
		dup2(list->outfile, 1);
	}
	else
	{
		// printf("%s\n", acs1);
		// printf("hhhhere am duping 1 with pipe\n");
		dup2(pipes->fd[0][1], 1);
	}
	// return ;
	// dprintf(2, "****%s, int fd : %d\n", get_next_line(list->infile), list->infile);
	// close(pipes->fd[0][0]);
	close(pipes->fd[0][1]);
	close(pipes->fd[1][0]);
	close(pipes->fd[1][1]);
	execve(acs1, list->cmd, env);
	ft_fail('e');
}

void	child_process_two(t_mini *list, char **env, t_pipe *pipes, int check)
{
	char	**ps_path;
	char	*acs2;
	char	**args;

	ps_path = pathfinder(env);
	if (!ps_path)
		exit(1);
	// args = ft_split(av[i], ' ');
	// printf("f0 === %d   f1 ===   %d\n", pipes->f0, pipes->f1);
	acs2 = check_access(ps_path, list->cmd[0]);
	// if (list->infile != -3)
	dup2(pipes->fd[pipes->f0][0], 0);
	if (check > 0)
	{
		// printf("am here for strinn\n");
		dup2(pipes->stdiin, 0);
	}
	// if (list->outfile != -3)
	dup2(pipes->fd[pipes->f1][1], 1);
	close(pipes->fd[pipes->f0][0]);
	close(pipes->fd[pipes->f0][1]);
	close(pipes->fd[pipes->f1][0]);
	close(pipes->fd[pipes->f1][1]);
	execve(acs2, list->cmd, env);
	ft_fail('e');
}

void	last_child(t_mini *list, char **env, t_pipe *pipes)
{
	char	**ps_path;
	char	*acs2;
	char	**args;
	int		fd2;

	// dprintf (2, "444 %s\n", get_next_line(5));
	// fd2 = open (av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0777);
	// printf("child get == %s\n", get_next_line(pipes->stdiin));
	if (list->outfile == -1)
		ft_fail('f');
	ps_path = pathfinder(env);
	if (!ps_path)
		exit(1);
	// args = ft_split(av[ac - 2], ' ');
	// printf("hrere\n");
	// printf("infile ==  %d outfile == %d\n", list->infile, list->outfile);
	acs2 = check_access(ps_path, list->cmd[0]);
	// printf("%s\n", acs2);
	// printf("%d\n", list->infile);
	// printf("%d\n", list->outfile);
	if (list->infile == -3 && list->next)
	{
		printf("am here for duping inf\n");
		// printf("f0 == %d\n", pipes->fd[0][0]);
		dup2(pipes->stdiin, 0);
	}
	printf("c-----heck%d\n", pipes->check);
	if (list->outfile != -3)
	{
		// printf("am here for duping pipe with outf\n");
		// fprintf(stderr, "outfile %d\n", pipes->fd[0][0 ]);
		// printf("%d\n", list->outfile);
		// printf("duping out with pipe\n");
		pipes->check++;
		printf("check%d\n", pipes->check);
		dup2(list->outfile, 1);
	}
	if(list->outfile != 1)
	{
		printf("am closed the file\n");
		close(list->outfile);
	}
	// close(pipes->stdiin);
	close(pipes->fd[pipes->f0][0]);
	close(pipes->fd[pipes->f0][1]);
	close(pipes->fd[pipes->f1][0]);
	close(pipes->fd[pipes->f1][1]);
	// printf("%s\n", acs2);
	// dprintf(2, "***%s,    pipe : %d\n", get_next_line(5), pipes->fd[0][0]);
	execve(acs2, list->cmd, env);
	ft_fail('e');
}
