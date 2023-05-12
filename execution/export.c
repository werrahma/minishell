/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:07:11 by werrahma          #+#    #+#             */
/*   Updated: 2023/05/12 18:57:07 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_value(char *str, t_env *lst)
{
	int i;
	int j;

	i = 0;

	while(str[i] && str[i] != '=')
		i++;
	i++;
	j = i;
	while(str[j])
		j++;
	lst->value = malloc(j + 1);
	while(str[i])
	{
printf("%c\n", str[i]);
		lst->value[i] = str[i];
		i++;
	}
	// lst->value[i] = '\0';
	printf("%s\n", lst->value);
}

void	dup_key(char *str, t_env *lst)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[j] && str[j] != '=')
		j++;
	lst->key = malloc(i + 1);
	i = 0;
	// exit(1);
	while (str && i < j)
	{
		lst->key[i] = str[i];
		i++;
	}
	lst->key[i] = '\0';
	printf("%s\n", lst->key);
	
}

// void	split_byequals(t_env *env, char *str)
// {
// 	int	i;

// 	i = 0;
// 	// while(str[i] && str[i] != '=')
// 	// {
// 		env->key = ft_strdup(str - ft_strlen(str));
// 	// }
// 		printf("%s\n", env->key);
// 		exit(1);
// 	while(str[i])
// 	{
// 		env->value = ft_strdup(str + ft_strlen(str));
// 		i++;
// 	}
// }

// void	export_arg(char *av)
// {	
// }

void	my_export(t_env **env, char **av)
{
	int	i;
	int	j;
    t_env *tmp;

	i = 2;
	j = 0;
	tmp = *env;
	// printf("%s\n", av[i]);
	// exit(1);
	while(av[i])
	{
		ft_lstadd_back(env, ft_lstnew(1));
		*env = ft_lstlast(*env);
		// split_byequals(*env, av[i]);
		dup_key(av[i], *env);
		dup_value(av[i], *env);
		i++;
	}
	exit(1);
	while (tmp)
	{
		printf("%s\n", tmp->key);
		tmp = tmp->next;
	}
}