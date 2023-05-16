/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <werrahma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 10:33:42 by yahamdan          #+#    #+#             */
/*   Updated: 2023/05/14 20:30:26 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_it(int fd, char *dst)
{
	char	*buff;
	int		rd;

	buff = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buff)
		return (NULL);
	while (!ft_strchr(buff, '\n'))
	{
		rd = read(fd, buff, BUFFER_SIZE);
		if (rd == -1)
			return (free(dst), free(buff), NULL);
		if (rd == 0)
			break ;
		buff[rd] = '\0';
		dst = ft_strjoin(dst, buff);
	}
	free(buff);
	return (dst);
}

char	*get_the_line(char *dst)
{
	char	*buff;
	int		i;
	int		tmp;

	i = 0;
	while (dst[i] && dst[i] != '\n')
		i++;
	if (dst[i] == '\n')
		i++;
	buff = malloc(sizeof(char) * (i + 1));
	if (!buff)
		return (NULL);
	tmp = i;
	i = 0;
	while (i < tmp)
	{
		buff[i] = dst[i];
		i++;
	}
	buff[i] = '\0';
	return (buff);
}

char	*get_the_next(char *dst)
{
	char	*tmp;
	char	*tmp1;

	tmp = ft_strchr(dst, '\n');
	if (!tmp)
		return (free(dst), NULL);
	if (!tmp[1])
		return (free(dst), NULL);
	tmp1 = ft_strdup(tmp + 1);
	free(dst);
	return (tmp1);
}

char	*get_next_line(int fd)
{
	static char	*dst;
	char		*line;

	if (fd < 0 || fd > 10240 || BUFFER_SIZE <= 0)
		return (NULL);
	dst = read_it(fd, dst);
	if (!dst)
		return (NULL);
	line = get_the_line(dst);
	dst = get_the_next(dst);
	return (line);
}
