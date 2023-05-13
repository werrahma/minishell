/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:07:11 by werrahma          #+#    #+#             */
/*   Updated: 2023/05/13 18:46:06 by werrahma         ###   ########.fr       */
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
	j = 0;
	while(str[i])
	{
		lst->value[j] = str[i];
		i++;
		j++;
	}
	lst->value[j] = '\0';
	// printf("%s\n", lst->value);
	// printf("here\n");
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
	// printf("%s\n", lst->key);
	
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

void	if_plus(char *arg, t_env *env)
{
	int i;

	i = 0;
	while(arg[i])
	{
		if (arg[i] == '+' && arg[i + 1] == '=')
		{
			env->value = ft_strjoin(env->value, arg);
			return ;
		}
		i++;
	}
}

int	check_exporting(t_env *env, char *arg)
{
	while(env)
	{
		if (!ft_strncmp(env->key, arg, ft_strlen(env->key)))
		{
			if_plus(arg, env);
			return (1);
		}
		env = env->next;
	}
	return (0);
}

void	my_export(t_env **env, char **av)
{
	int	i;
	int	j;
    t_env *tmp;

	i = 2;
	j = 0;
	tmp = *env;
	// if(str_len(av) == 1)
	// {
		// printf("han\n");
		sort_list(env);
	// }
	// exit(1);
	while(av[i])
	{
		if(check_exporting(*env, av[i]));
		else
		{
			ft_lstadd_back(env, ft_lstnew(1));
			*env = ft_lstlast(*env);
			dup_key(av[i], *env);
			dup_value(av[i], *env);
		}
		i++;
	}
	*env = tmp;
	// while (tmp)
	// {
	// 	printf("%s\n", tmp->key);
	// 	tmp = tmp->next;
	// }
	// exit(1);
}
