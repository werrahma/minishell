/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:22:26 by werrahma          #+#    #+#             */
/*   Updated: 2023/05/05 13:38:14 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **env)
{
    int i = 0;
    int j;
    char **hold;
    t_env   *list = NULL;
    t_env   *tmp = NULL;

	create_list(&list, env);
	tmp = list;
    while(env[i])
    {
		j = 0;
		hold = ft_split(env[i], '=');
		while (j < 2)
		{
		    list->key = hold[j];
		    j++;
			list->value = hold[j];
			j++;
		}
		list = list->next;
		i++;
    }
	list = tmp;
	
	i = 0;
	while (tmp)
	{
		// printf("%d\n", i);
		// i++;
		printf("key == %s   value == %s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}

}