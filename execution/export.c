/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:07:11 by werrahma          #+#    #+#             */
/*   Updated: 2023/06/05 19:06:15 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env **env)
{
	t_env *tmp;

	while (*env)
	{
		tmp = *env;
		free((*env)->key);
		free((*env)->value);
		*env = (*env)->next;
		free(tmp);
	}
	// free(env);
}

t_env	*fond_key(t_env *list, char *str)
{
	while (list)
	{
		if (!ft_strncmp(list->key, str, ft_strlen(list->key)))
			return (list);
		list = list->next;
	}
	return (NULL);
}

void	dup_value(char *str, t_env *lst)
{
	int i;
	int j;

	i = 0;
	while(str[i] && str[i] != '=')
		i++;
	if(str[i] == '=')
		i++;
	j = i;
	while(str[j])
		j++;
	lst->value = malloc(j + 1);
	// lst->value = NULL;
	j = 0;
	while(str[i])
	{
		lst->value[j] = str[i];
		i++;
		j++;
	}
	if (j == 0)
		lst->value = NULL;
	else
		lst->value[j] = '\0';
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
	lst->key = malloc(j + 1);
	i = 0;
	// exit(1);
	while (str && i < j)
	{
		lst->key[i] = str[i];
		i++;
	}
	lst->key[i] = '\0';
	// printf("---%s\n", lst->key);
	
}

void	if_plus(char *arg, t_env *env)
{
	int i;

	i = 0;
	while(arg[i])
	{
		if (arg[i] == '+' && arg[i + 1] == '=')
		{
			printf("last value is ->> %s\n", env->value);
			printf("arg is === %s\n", arg);
			env->value = ft_strjoin(env->value, arg);
			printf("new value is ->> %s\n", env->value);
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
    t_env	*tmp;
	t_env	*c_env;

	i = 1;
	j = 0;
	tmp = *env;
	c_env = NULL;
	if(str_len(av) == 1)
	{
		copy_env(env, &c_env);
		sort_list(&c_env);
		while((c_env))
		{
			// if ((c_env)->value)
			// {
			printf("declare -x ");
			printf("%s", (c_env)->key);
			if ((c_env)->value)
			{
				printf("=");
				printf("%s\n", (c_env)->value);
			}
			else
				printf("\n");
			(c_env) = (c_env)->next;
		}
		free_env(&c_env);
	}
	else
	{
		while(av[i])
		{
			if(check_exporting(*env, av[i]))
			{
				// printf("am here\n");
				// printf("%s\n", av[i]);
				// dup_key(av[i], *env);
				*env = fond_key(*env, av[i]);
				dup_value(av[i], *env);
			}
			else
			{
				ft_lstadd_back(env, ft_lstnew(1));
				*env = ft_lstlast(*env);
				dup_key(av[i], *env);
				dup_value(av[i], *env);
			}
			i++;
		}
	}
	// printf("hna\n");
	*env = tmp;
	// while((*env))
	// {
	// 	if ((*env)->value)
	// 	{
	// 		printf("declare -x ");
	// 		printf("%s", (*env)->key);
	// 		printf("=");
	// 		printf("%s\n", (*env)->value);
	// 	}
	// 	(*env) = (*env)->next;
	// }
	// *env = tmp;
	// exit(1);
}
