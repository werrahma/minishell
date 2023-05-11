/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahamdan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 21:46:33 by yahamdan          #+#    #+#             */
/*   Updated: 2023/05/10 13:54:24 by yahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	return (fd);
}

t_mini	*creat_list(t_tokens *tokens)
{
	t_mini	*list = NULL;
	int i = 1;

	while(tokens)
	{
		if(tokens->type == 2)
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
	while (token)
	{
		if(token->type == 2)
		{
			list = list->next;
			i = 0;
		}
		else if ((token->type == 3 || token->type == 5 || token->type == 4))
		{
			list->cmd = realloc(list->cmd, (i + 1) * sizeof(char *));
			list->cmd[i] = ft_strdup(token->cont);
			i++;
		}
		else if (token->next && token->type == INPUT)
			list->infile = openfd(token->next->cont, 0);	
		else if (token->next &&  token->type == OUTPUT)
		{
			//printf("**%d\n", list->outfile);
			list->outfile = openfd(token->next->cont, 1);
		}
		else if (token->next && token->type == APPEND)
		{
			list->outfile = openfd(token->next->cont, 2);
		}
		//printf("%d\n" , token->type);
		token = token->next;
	}
	list = tmp;
	return (list);

}

// t_mini  *fill_last_list(t_tokens *token)
// {
// 	t_mini  *mill;
// 	t_mini  *tmp;
// 	int		i;
// 	mill = NULL;
// 	while(token && token->next)
// 	{
// 		ft_lstadd_backl(&mill, ft_lstnewl());
// 		tmp = ft_lstlastl(mill);
// 		while(token && token->next && token->type != PIPE)
// 		{
// 			i = 0;
// 			while (token && (token->type == 3 || token->type == 5 || token->type == 4))
// 			{
// 				tmp->cmd = realloc(tmp->cmd,  (i + 1) * sizeof(char *));
// 				tmp->cmd[i] = ft_strdup(token->cont);
// 				token = token->next;
// 				i++;
// 			}
// 			if (token && token->next && token->type == INPUT)
// 			{
			
// 				tmp->infile = openfd(token->next->cont, 0);
// 			}
// 			else if (token && token->next &&  token->type == OUTFILE)
// 			{
// 				tmp->outfile = openfd(token->next->cont, 1);
// 			}
// 			// exit(1);
// 			else if (token && token->next && token->type == APPEND)
// 			{
// 				tmp->outfile = openfd(token->next->cont, 2);
// 			}
// 			else 
// 			{
// 				tmp->infile = 0;
// 				tmp->outfile = 1;
// 				// break;
// 			}
// 		//	printf("%s\n", tmp->cmd[i - 1]);
// 			if(token)
// 				token = token->next;
// 		}
// 		if (token)
// 			token = token->next; 
// 	}
// 	return (mill);
// }