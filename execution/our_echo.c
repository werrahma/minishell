/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:09:30 by werrahma          #+#    #+#             */
/*   Updated: 2023/06/21 18:17:53 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_echo(char *s)
{
	size_t	i;

	i = 1;
	if ((s[0] == '-' && ft_strlen(s) == 1) || ft_strlen(s) == 1)
		return (0);
	while (i < ft_strlen(s))
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	print_cho(char **s, int i, int check)
{
	int	flag;
	int	flag2;

	flag = 0;
	flag2 = 0;
	if (check_echo(s[i]))
		flag = 1;
	while (s[i])
	{
		if (flag == 1)
		{
			if (!check_echo(s[i]))
			{
				flag = 0;
				printf("%s", s[i]);
			}
		}
		else
			printf("%s", s[i]);
		i++;
		if (s[i] && !check_echo(s[i - 1]))
			printf(" ");
	}
	if (check == 0)
		printf("\n");
}

int	our_echo(char **str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (str_len(str) <= 1 || !str[1][0])
		printf("\n");
	else if (str_len(str) == 2 && check_echo(str[1]))
		;
	else if (str[1][0] == '-')
	{
		if (!check_echo(str[i + 1]))
			return (print_cho(str, i + 1, 0), status_checker(0));
		else
			return (print_cho(str, i + 2, 1), status_checker(0));
	}
	else
		return (print_cho(str, i + 1, 0), status_checker(0));
	return (status_checker(0));
}
