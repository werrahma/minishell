/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <werrahma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 12:46:05 by werrahma          #+#    #+#             */
/*   Updated: 2023/06/16 23:44:58 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	str_len(char **av)
{
	int	i;

	i = 0;
	while(av[i])
		i++;
	return (i);
}

int	check_exit_arg(char *av)
{
	int	i;

	i = 0;
	if (av[i] == '+' || av[i] == '-')
		i++;
	while(av[i])
	{
		if (!(av[i] >= '0' && av[i] <= '9'))
		{
			write(2, "numeric argument required\n", 26);
			return (0);
		}
		i++;
	}
	return (ft_atoi(av));
}


int	my_exit(char **av)
{
	int	i;
	int	flag;
	int	status;

	i = 0;
	flag = 0;
	write(2, "exit\n", 5);
	if (str_len(av) > 2 && (av[1][0] >= '0' && av[1][0] <= '9'))
	{
		write(1, "too many arguments\n", 19);
		return (-1);
	}
	else if (!av[1])
		status = 127;
	else if(av[1] && !check_exit_arg(av[1]))
	{
		status = 255;
	}
	else
		status = ft_atoi(av[1]);
	if (status > 255)
		status = status % 256;
	else if (status < 0)
		status = status + 256;
	return (status);
	
}
