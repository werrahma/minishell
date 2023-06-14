/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:07:11 by werrahma          #+#    #+#             */
/*   Updated: 2023/06/14 18:01:17 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_spas_instring(char *str)
{
	int	i;

	i = 0;
	while(str[i] && str[i] != '=')
	{
		if (str[i] == ' ' || str[i] == '-' || (str[0] >= '0' && str[0] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

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
	if (str[j] && !str[j + 1])
		j++;
	lst->key = malloc(j + 1);
	while (str && i < j)
	{
		lst->key[i] = str[i];
		i++;
	}
	lst->key[i] = '\0';
	// printf("---%s\n", lst->key);
	
}

int	has_plus_equal(char *arg, t_env *env)
{
	int i;

	i = 0;
	while(arg[i])
	{
		if (arg[i] == '+' && arg[i + 1] == '=')
		{
			// printf("last value is ->> %s\n", env->value);
			// printf("arg is === %s\n", arg);
			env->value = ft_strjoin(env->value, &arg[i + 2]);
			// printf("new value is ->> %s\n", env->value);
			return (1);
		}
		i++;
	}
	return (0);
}

int	is_plus_equal_inlist(t_env *env, char *arg)
{
	while(env)
	{
		if (!ft_strncmp(env->key, arg, ft_strlen(env->key)))
		{
			if(has_plus_equal(arg, env))
				return (1);
			else
				return (0);
		}
		env = env->next;
	}
	return (0);
}
int	is_string_inlist(t_env *env, char *arg)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	// printf("arg ->>>> %s\n", arg);
	while(arg[i] && arg[i] != '=')
		i++;
	if (arg[i] && !arg[i + 1])
		flag = 1;
	while(env)
	{
		if (!ft_strncmp(env->key, arg, ft_strlen(env->key)))
		{
			// free(env->key);
			if (flag == 1)
				env->key = ft_strdup(arg);
			return (1);
		}
		env = env->next;
	}
	return (0);
}

void	our_export(t_env **env, char **av)
{
	int			i;
	int			j;
    t_env		*tmp;
	t_env		*c_env;
	static int	cnst;

	i = 1;
	j = 0;
	tmp = *env;
	c_env = NULL;
	if (!tmp)
		cnst = 0;
	if(str_len(av) == 1)
	{
		copy_env(env, &c_env);
		sort_list(&c_env);
		while((c_env))
		{
				printf("declare -x ");
				printf("%s", (c_env)->key);
			if ((c_env)->value != NULL)
			{
				// printf("/;;");
				printf("=");
				printf("\"");
				printf("%s", (c_env)->value);
				printf("\"\n");
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
			if (is_plus_equal_inlist(*env, av[i]));
			else if(is_string_inlist(*env, av[i]))
			{
				// printf("am here\n");
				// printf("%s\n", av[i]);
				// dup_key(av[i], *env);
				*env = fond_key(*env, av[i]);
				dup_value(av[i], *env);
			}
			else
			{
				if (!is_spas_instring(av[i]))
				{
					printf("minishell: export: %s: not a valid identifier\n", av[i]);
					break ;
				}
				ft_lstadd_back(env, ft_lstnew(1));
				*env = ft_lstlast(*env);
				if (!tmp && !cnst)
				{
					tmp = *env;
					cnst++;
				}
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
