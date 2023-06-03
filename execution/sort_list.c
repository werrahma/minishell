
#include "minishell.h"

void	copy_env(t_env **env, t_env **c_env)
{
	t_env *c_tmp;
	t_env *tmp;
	t_env *cc;

	tmp = *env;
	printf("here\n");
		ft_lstadd_back(&cc, ft_lstnew(1));
	while(1);
	while (*env && (*env)->next)
	{
		*env = (*env)->next;
	}
	while(1);
	c_tmp = *c_env;
	while (c_env && env)
	{
		(*c_env)->key = ft_strdup((*env)->key);
		(*c_env)->value = ft_strdup((*env)->value);
		*env = (*env)->next;
		*c_env = (*c_env)->next;
	}
	*c_env = c_tmp;
}

void	sort_list(t_env **env)
{
	t_env *tmp;
	char *key_swaping;
	char *value_swaping;

	tmp = *env;

	while(*env && (*env)->next)
	{
		if (ft_strncmp((*env)->key, (*env)->next->key, 1) >= 1)
		{
			key_swaping = (*env)->next->key;
			(*env)->next->key = (*env)->key;
			(*env)->key = key_swaping;

			value_swaping = (*env)->next->value;
			(*env)->next->value = (*env)->value;
			(*env)->value = value_swaping;
			// value_swaping = (*env)->next->value;
			// (*env)->next->value = value_swaping;
			// key_swaping = (*env);
			*env = tmp;
		}
		else
			*env = (*env)->next;
	}
	// printf("%s\n", (*env)->key);
	*env = tmp;
	// while(*env)
	// {
	// 	printf("%s == ", (*env)->key);
	// 	printf("%s\n", (*env)->value);
	// 	(*env) = (*env)->next;
	// }
	// exit(1);
}