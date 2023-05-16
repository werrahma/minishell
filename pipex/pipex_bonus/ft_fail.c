/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fail.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 22:28:55 by werrahma          #+#    #+#             */
/*   Updated: 2023/02/20 23:13:47 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_fail(char av)
{
	if (av == 'f')
	{
		write(1, "open failed\n", 12);
		exit(1);
	}
	else if (av == 'e')
	{
		write(2, "\nexecve->fail\n", 14);
		exit(1);
	}
	else if (av == 'a')
	{
		write(1, "bad arguments bye", 17);
		exit(1);
	}
}
