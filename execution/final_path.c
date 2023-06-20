/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 11:36:22 by werrahma          #+#    #+#             */
/*   Updated: 2023/06/19 22:10:00 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**pass_split(char *path)
{
	char	*n_path;
	char	**sp;

	n_path = ft_strdup(&path[5]);
	sp = ft_split(n_path, ':');
	if (!sp)
		our_free(sp);
	free(n_path);
	return (sp);
}

char	**pathfinder(t_env *env)
{
	while(env)
	{
		if (!ft_strncmp("PATH", env->key, 4))
			return (pass_split(env->value));
		env = env->next;
	}
	return (NULL);
}
