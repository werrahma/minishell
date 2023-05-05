/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:22:22 by werrahma          #+#    #+#             */
/*   Updated: 2023/02/21 22:18:58 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	here_doc(char **av, int ac)
{
	int		fd_h;
	char	*str;
	char	*s;

	fd_h = ft_checker(ac, av[1]);
	s = ft_strjoin(av[2], "\n");
	while (1)
	{
		write (1, "here_doc > ", 11);
		str = get_next_line(0);
		if (str == NULL)
		{
			free(s);
			return (1);
		}
		if (ft_strncmp(s, str, size_lim(str, av[2])) == 0)
			break ;
		write(fd_h, str, ft_strlen(str));
		free(str);
	}
	free(str);
	free(s);
	close (fd_h);
	return (1);
}
