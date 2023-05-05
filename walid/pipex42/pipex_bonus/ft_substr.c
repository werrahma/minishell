/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <werrahma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 10:22:13 by werrahma          #+#    #+#             */
/*   Updated: 2023/02/08 20:14:19 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	b;
	char	*m;

	b = 0;
	if (s == NULL)
		return (NULL);
	if (ft_strlen(s) <= (size_t)start)
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	m = malloc((len + 1) * sizeof(char));
	if (m == NULL)
		return (NULL);
	while (s[start] && b < len)
	{
		m[b] = s[start];
		b++;
		start++;
	}
	m[b] = '\0';
	return (m);
}
