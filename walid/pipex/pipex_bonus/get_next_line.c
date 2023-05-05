/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 16:21:31 by werrahma          #+#    #+#             */
/*   Updated: 2023/02/21 16:36:09 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	strlen1(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\n' && s[i])
		i++;
	if (s[i] == '\n')
		i++;
	return (i);
}

int	search(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}

char	*ft_read(int fd, char *p)
{
	char	*m;
	ssize_t	ret;

	ret = 1;
	m = malloc(sizeof(char) * (size_t)BUFFER_SIZE + 1);
	if (!m)
		return (NULL);
	m[0] = '\0';
	while (search(m) && ret)
	{
		ret = read(fd, m, BUFFER_SIZE);
		if (ret == -1)
			return (free(m), free(p), NULL);
		if (!ret)
		{
			free (m);
			return (p);
		}
		m[ret] = '\0';
		p = get_strjoin(p, m);
	}
	free (m);
	return (p);
}

char	*ft_free(char *p, char *line)
{
	char	*tmp;

	tmp = ft_strdup(p);
	free(p);
	p = ft_strdup(tmp + ft_strlen(line));
	free(tmp);
	return (p);
}

char	*get_next_line(int fd)
{
	static char	*p;
	char		*line;
	int			i;

	i = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	p = ft_read (fd, p);
	if (!p)
		return (0);
	line = malloc(strlen1(p) + 1);
	while (i < strlen1(p))
	{
		line[i] = p[i];
		i++;
	}
	line[i] = '\0';
	if (ft_strlen(p) > ft_strlen(line))
		p = ft_free (p, line);
	else
	{
		free (p);
		p = NULL;
	}
	return (line);
}
