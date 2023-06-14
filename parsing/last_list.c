/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 21:46:33 by yahamdan          #+#    #+#             */
/*   Updated: 2023/06/14 11:42:42 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution/minishell.h"

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
	lst->infile = -3;
	lst->outfile = -3;
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
	extern int stx;
	int fd;
	if (i == 0)
	{
		fd = open(file, O_RDONLY);
		if (fd == -1)
		{
			ft_putstr_fd(ft_strjoin(file , " :"), 2);
			ft_putstr_fd(" no such file or directory\n", 2);
			stx = 1;
		}
	}
	else if (i == 1)
	{
		fd = open(file , O_CREAT | O_RDWR | O_TRUNC, 0777);
		if (fd == -1)
		{
			ft_putstr_fd(" : no such file or directory\n", 2);
			stx = 1;
		}
	}
	else if (i == 2)
	{
		fd = open(file , O_CREAT | O_RDWR | O_APPEND, 0777);
		if (fd == -1)
		{
			ft_putstr_fd(ft_strjoin(file , " :"), 2);
			ft_putstr_fd(" no such file or directory\n", 2);
			stx = 1;
		}
	}
	else if (i == 3)
		fd = open(file , O_RDWR | O_APPEND , 0777);
	// printf("%d\n", fd);
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
void	*ft_realloc(void *ptr, size_t size)
{
	void *nptr;
	size_t len;

	if (ptr == NULL)
	{
		ptr = malloc(size);
		return (ptr);
	}
	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	nptr = malloc(size);
	if (!nptr)
		return (NULL);
	len = size;
	ft_memcpy(nptr, ptr, len);
	free(ptr);
	return (nptr);
}

t_mini	*fill_last_list(t_tokens *token, t_env *lis)
{
	t_mini *list;
	t_mini	*tmp;
	int		i;


	i = 0;
	int flag = 0;
	ft_maxheropn(token);
	if (!stxe(token))
	{
		list = creat_list(token);
		tmp = list;
		open_herfiles(token, lis);
		while (token)
		{
			if (!token->cont && !token->next && token->type == ARG)
			{
				list->cmd = ft_realloc(list->cmd, (i + 1) * sizeof(char *));
				list->cmd[i] = ft_strdup(token->cont);
				i++;
			}
			else if(token && token->type == ARG && !token->cont && token->next);
			else if(token && token->type == PIPE)
			{
				list->cmd = ft_realloc(list->cmd, (i + 1) * sizeof(char *));
				list->cmd[i] = NULL;
				list = list->next;
				i = 0;
			}
			else if (token && token->type == ARG && token->cont)
			{

				list->cmd = ft_realloc(list->cmd, (i + 1) * sizeof(char *));
				list->cmd[i] = ft_strdup(token->cont);
				i++;
			}
			else if (token && token->next && token->type == HEREDOC && token->next->type == LIMETER)
			{
				list->infile = openfd(token->next->cont, 3);
				printf("[%d]\n", list->infile);
			}
			else if (token && token->next && token->type == INPUT && token->next->type == INFILE)
				list->infile = openfd(token->next->cont, 0);
			else if (token && token->next &&  token->type == OUTPUT && token->next->type == OUTFILE)
			{
				list->outfile = openfd(token->next->cont, 1);
			}
			else if (token && token->next && token->type == APPEND && token->next->type == OUTFILE)
				list->outfile = openfd(token->next->cont, 2);
			else if (token && (token->type == INPUT || token->type == OUTPUT) && !token->next)
			{
				list->outfile = -1;
			}
			token = token->next;
		}
		list->cmd = ft_realloc(list->cmd, (i + 1) * sizeof(char *));
		list->cmd[i] = NULL;
		list = tmp;
		return (list);
	}
	return (NULL);
}
