/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 11:36:22 by werrahma          #+#    #+#             */
/*   Updated: 2023/02/22 17:27:51 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_split(char **sp)
{
	int	i;

	i = 0;
	while (sp)
		free(sp[i++]);
	free(sp);
}

char	**pass_split(char *path)
{
	char	*n_path;
	char	**sp;

	n_path = ft_strdup(&path[5]);
	sp = ft_split(n_path, ':');
	if (!sp)
		free_split(sp);
	free(n_path);
	return (sp);
}

char	**pathfinder(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
			return (pass_split(env[i]));
		i++;
	}
	return (NULL);
}
