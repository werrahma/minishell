
#include "minishell.h"

void	sort_list(t_env **env)
{
	t_env *tmp;
	char *key_swaping;
	char *value_swaping;

	tmp = *env;

	// printf("%d\n", ft_strncmp("zlid", "walid", 1));
	// exit(1);
	printf("am here\n");
	while(*env && (*env)->next)
	{
		if (ft_strncmp((*env)->key, (*env)->next->key, 1) > 1)
		{
			// printf("declare -x");
			// printf(" ");
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
		{
			// printf("hjds\n");
			*env = (*env)->next;
		}
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