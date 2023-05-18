/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 11:33:48 by werrahma          #+#    #+#             */
/*   Updated: 2023/02/22 17:02:44 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_strjoin(char *s1, char *s2)
{
	int		a;
	int		b;
	char	*m;

	a = -1;
	b = -1;
	if (!s1 && s2)
		return (ft_strdup(s2));
	if (s1 && !s2)
		return (ft_strdup(s1));
	m = malloc((ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!m)
		return (0);
	while (s1[++a])
		m[a] = s1[a];
	while (s2[++b])
		m[a + b] = s2[b];
	m[a + b] = '\0';
	free(s1);
	return (m);
}

char	*check_access(char **ps_path, char *av)
{
	int	i;

	i = 0;
	if (av[0] == '/')
		return (av);
	av = ft_strjoin("/", av);
	while (ps_path[i])
	{
		ps_path[i] = get_strjoin(ps_path[i], av);
		if (access(ps_path[i], X_OK) != -1)
		{
			free(av);
			return (ps_path[i]);
		}
		i++;
	}
	write(1, av + 1, ft_strlen(av));
	write(1, " :command not found\n", 21);
	exit(1);
}
