/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 21:46:33 by yahamdan          #+#    #+#             */
/*   Updated: 2023/05/14 16:31:46 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "p_minishell.h"

void	ft_lstadd_backl(t_mini **lst, t_mini *new)
{
	t_mini	*tmp;

	tmp = ft_lstlastl(*lst);
	if (!lst || !new)
		return ;
	if (*lst == NULL )
		(*lst) = new;
	else
		ft_lstlastl(*lst)->next = new;
}

t_mini	*ft_lstnewl(void)
{
	t_mini	*lst;

	lst = malloc(sizeof(t_mini));
	if (!lst)
		return (NULL);
	lst->next = NULL;
	lst->cmd  = NULL;
	lst->infile = 0;
	lst->outfile = 1;
	return (lst);
}

t_mini	*ft_lstlastl(t_mini *lst)
{
	if (!lst)
		return (NULL);
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);

}

int openfd(char *file, int i)
{
	int fd;
	if (i == 0) 
		fd = open(file, O_RDONLY);
	else if (i == 1)
		fd = open(file , O_CREAT | O_RDWR | O_TRUNC, 0777);
	else if (i == 2)
		fd = open(file , O_CREAT | O_RDWR | O_APPEND, 0777);
	else if (i == 3)
		fd = open(file , O_RDWR | O_APPEND, 0777);
	return (fd);
}

t_mini	*creat_list(t_tokens *tokens)
{
	t_mini	*list = NULL;
	int i = 1;

	while(tokens)
	{
		if(tokens->type == PIPE)
			i++;
		tokens = tokens->next;
	}

	while(i > 0)
	{
		ft_lstadd_backl(&list, ft_lstnewl());
		i--;
	}
	return (list);
}

t_mini	*fill_last_list(t_tokens *token)
{
	t_mini *list;
	t_mini	*tmp;
	int		i;

	list = creat_list(token);
	tmp = list;

	i = 0;
	open_herfiles(token);
	while (token)
	{
		//printf("ls\n");
		if(token->type == PIPE)
		{
			list = list->next;
			i = 0;
		}
		else if (token->type == 5)
		{
			list->cmd = realloc(list->cmd, (i + 1) * sizeof(char *));
			list->cmd[i] = ft_strdup(token->cont);
			i++;
		}
		else if (token->next && token->type == HEREDOC)
			list->infile = openfd(token->next->cont, 3);
		else if (token->next && token->type == INPUT)
			list->infile = openfd(token->next->cont, 0);	
		else if (token->next &&  token->type == OUTPUT)
			list->outfile = openfd(token->next->cont, 1);
		else if (token->next && token->type == APPEND)
			list->outfile = openfd(token->next->cont, 2);
		token = token->next;
	}
	list = tmp;
	return (list);

}
