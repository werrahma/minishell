/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_limiter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:19:47 by werrahma          #+#    #+#             */
/*   Updated: 2023/02/21 22:33:54 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	size_lim(char *str, char *av)
{
	int	size;

	size = ft_strlen(str);
	if (ft_strlen(av) > ft_strlen(str))
		size = ft_strlen(av);
	return (size);
}

int	ft_checker(int ac, char *av)
{
	int	fd_h;

	if (ac < 6)
	{
		write(1, "bad arguments bye", 17);
		exit(1);
	}
	fd_h = open (av, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fd_h < 0)
	{
		write(2, "\nopen failed \n", 14);
		exit(1);
	}
	return (fd_h);
}
