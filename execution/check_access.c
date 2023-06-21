/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 11:33:48 by werrahma          #+#    #+#             */
/*   Updated: 2023/06/20 20:35:53 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_access(char **ps_path, char *av)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (av[0] == '/' || (av[0] == '.' && av[1] == '/'))
		return (av);
	if (!av[0])
		flag = 1;
	av = ft_strjoin("/", av);
	while (ps_path[i] && !flag)
	{
		ps_path[i] = ft_strjoin(ps_path[i], av);
		if (access(ps_path[i], X_OK) != -1)
		{
			free(av);
			return (ps_path[i]);
		}
		i++;
	}
	write(1, av + 1, ft_strlen(av + 1));
	write(1, " :command not found\n", 21);
	return (0);
}
