/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help2_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 19:55:03 by werrahma          #+#    #+#             */
/*   Updated: 2023/06/21 14:11:26 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	status_checker(int exit_status)
{
	extern int	stx;

	stx = exit_status;
	return (stx);
}

int	has_plus_equal(char *arg, t_env *env)
{
	char	*tmp;
	int		i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '+' && arg[i + 1] == '=')
		{
			tmp = env->value;
			env->value = ft_strjoin(env->value, &arg[i + 2]);
			free(tmp);
			return (1);
		}
		i++;
	}
	return (0);
}

int	is_plus_equal_inlist(t_env *env, char *arg)
{
	char	**str;

	str = ft_split(arg, '+');
	while (env)
	{
		if (!ft_strncmp(env->key, str[0], ft_strlen(str[0])))
		{
			our_free(str);
			if (has_plus_equal(arg, env))
				return (1);
			else
				return (0);
		}
		env = env->next;
	}
	our_free(str);
	return (0);
}

void	for_dup(t_env *env, char *av)
{
	env = fond_key(env, av);
	free((env)->value);
	dup_value(av, env);
}

int	export_monitor(t_env **env, t_env **tmp, char *av, int *cnst)
{
	if (is_plus_equal_inlist(*env, av))
		;
	else if (is_string_inlist(*env, av))
		for_dup(*env, av);
	else
	{
		if (!is_spas_instring(av))
		{
			printf("minishell: export: %s: not a valid identifier\n", av);
			return (0);
		}
		ft_lstadd_back(env, ft_lstnew());
		*env = ft_lstlast(*env);
		if (!*tmp && !*cnst)
		{
			*tmp = *env;
			(*cnst)++;
		}
		dup_key(av, *env);
		dup_value(av, *env);
	}
	return (1);
}
