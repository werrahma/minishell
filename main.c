/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:22:26 by werrahma          #+#    #+#             */
/*   Updated: 2023/05/05 11:27:34 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **env)
{
    int i = 0;
    int j;
    char **hold;
    t_env   list;
    while(env[i])
    {
		j = 0;
		
		hold = ft_split(env[i], '=');
		while (hold[j])
		{
		    list.key = hold[j];
			list.value = hold[j];
		    j++;
		}
		i++;
    }
	i = 0;
	// while ()

}