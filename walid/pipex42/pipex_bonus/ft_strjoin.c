/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 11:09:10 by werrahma          #+#    #+#             */
/*   Updated: 2023/02/21 22:06:23 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#include "pipex.h"

char	*ft_strjoin(char *s1, char const *s2)
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
	return (m);
}
