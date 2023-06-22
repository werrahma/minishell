/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 21:51:22 by yahamdan          #+#    #+#             */
/*   Updated: 2023/06/22 22:42:05 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution/minishell.h"

void	handle_signal(int sig)
{
	(void) sig;
	g_status = 1;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	unlink_hf(void)
{
	char	*name;
	int		i;
	char	*ii;

	i = 0;
	ii = ft_itoa(i);
	name = ft_strjoin("/tmp/here_doc", ii);
	while (!access(name, F_OK))
	{
		i++;
		unlink(name);
		free(name);
		free(ii);
		ii = ft_itoa(i);
		name = ft_strjoin("/tmp/here_doc", ii);
	}
	free(name);
	free(ii);
}

void	free_li(t_mini **li)
{
	t_mini	*tmp;
	int		i;

	while (*li)
	{
		tmp = (*li);
		i = 0;
		while ((*li)->cmd[i])
		{
			free((*li)->cmd[i++]);
		}
		free((*li)->cmd);
		(*li) = (*li)->next;
		free((tmp));
	}
}

void	init(t_pipe *pipes, t_mini *li)
{
	pipes->size_list = ft_lstsize(li);
	pipes->pid = tab_pid(li);
	pipes->index = 0;
	pipes->f0 = 0;
	pipes->f1 = 1;
}
