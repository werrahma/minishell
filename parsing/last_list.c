/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahamdan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 21:46:33 by yahamdan          #+#    #+#             */
/*   Updated: 2023/06/20 17:59:29 by yahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution/minishell.h"

int	openfd(char *file, int i)
{
	extern int	stx;
	int			fd;
	char		*str;

	if (i == 0)
	{
		fd = open(file, O_RDONLY);
		if (fd == -1)
		{
			str = ft_strjoin(file, " :");
			ft_putstr_fd(str, 2);
			ft_putstr_fd(" no such file or directory\n", 2);
			stx = 1;
			free(str);
		}
	}
	else if (i == 1)
		fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0777);
	else if (i == 2)
		fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0777);
	else if (i == 3)
		fd = open(file, O_RDWR | O_APPEND, 0777);
	return (fd);
}

void	creat_list(t_tokens *tokens, t_mini **list)
{
	int	i;

	i = 1;
	while (tokens)
	{
		if (tokens->type == PIPE)
			i++;
		tokens = tokens->next;
	}
	while (i > 0)
	{
		ft_lstadd_backl(list, ft_lstnewl());
		i--;
	}
}

void	openfiles(t_tokens *token, t_mini **list)
{
	if (token && token->next && token->type == 6 && token->next->emg == 1)
		(*list)->infile = -1;
	else if (token && token->next && (token->type == 7 || token->type == 8)
		&& token->next->emg == 1)
		(*list)->outfile = -1;
	else if (token && token->next && token->type == 3
		&& ((*list)->infile != -1 && (*list)->outfile != -1))
		(*list)->infile = openfd(token->next->cont, 3);
	else if (token && token->next && token->type == 6
		&& ((*list)->infile != -1 && (*list)->outfile != -1))
		(*list)->infile = openfd(token->next->cont, 0);
	else if (token && token->next && token->type == 7
		&& ((*list)->infile != -1 && (*list)->outfile != -1))
		(*list)->outfile = openfd(token->next->cont, 1);
	else if (token && token->next && token->type == 8
		&& ((*list)->infile != -1 && (*list)->outfile != -1))
		(*list)->outfile = openfd(token->next->cont, 2);
}

void	fill(t_tokens *token, t_mini **list, int *i)
{
	while (token)
	{
		if (token && token->type == ARG && !token->cont && token->next)
			;
		else if (token && token->type == PIPE)
		{
			(*list)->cmd = ft_realloc((*list)->cmd, (*i + 1) * sizeof(char *));
			(*list)->cmd[*i] = NULL;
			(*list) = (*list)->next;
			*i = 0;
		}
		else if (token && token->type == ARG)
		{
			(*list)->cmd = ft_realloc((*list)->cmd, (*i + 1) * sizeof(char *));
			(*list)->cmd[*i] = ft_strdup(token->cont);
			(*i)++;
		}
		else
			openfiles(token, list);
		token = token->next;
	}
}

void	fill_last_list(t_tokens *token, t_env *lis, t_mini **list)
{
	t_mini		*tmp;
	t_tokens	*tm;
	int			i;
	int			flag;

	i = 0;
	flag = 0;
	ft_maxheropn(token);
	if (stxe(token))
	{
		free_tokens(token);
		return ;
	}
	creat_list(token, list);
	open_herfiles(token, lis);
	tmp = *list;
	fill(token, list, &i);
	free_tokens(token);
	(*list)->cmd = ft_realloc((*list)->cmd, (i + 1) * sizeof(char *));
	(*list)->cmd[i] = NULL;
	(*list) = tmp;
}
