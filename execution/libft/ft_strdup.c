/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 10:15:25 by werrahma          #+#    #+#             */
/*   Updated: 2023/06/21 16:23:45 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		a;
	int		b;
	char	*p;

	b = ft_strlen(s1);
	p = malloc(sizeof(char) * b + 1);
	if (!p)
		return (0);
	a = 0;
	while (s1[a])
	{
		p[a] = s1[a];
		a++;
	}
	p[a] = '\0';
	return (p);
}
