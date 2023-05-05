/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:49:08 by werrahma          #+#    #+#             */
/*   Updated: 2023/05/04 15:15:45 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main()
{
	char str[PATH_MAX];
	char *s;

	printf("%s\n", getcwd(str, PATH_MAX));

	chdir("./pipex");
	
	// free(s);
	printf("%s\n", getcwd(str, PATH_MAX));
	// free(s);
	while(1);
	
}