
#include "minishell.h"

void	sort_list(t_env **env)
{
	t_env *tmp;

	// tmp = *env;

	while(*env && (*env)->next)
	{
		if (cmp_env((*env)->key, (*env)->next->key) < 1)
		{
			tmp = (*env)->next;
			(*env)->next = tmp->next;
			// exit(2);
			tmp->next = (*env);
			*env = tmp;
		printf("%s\n", (*env)->key);
			// printf("am here\n");
			// tmp = (*head)->next;
			// (*head)->next = tmp->next;
			// tmp->next = (*head);
			// (*head) = tmp;
		}
		else
			*env = (*env)->next;
	}
	// *env = tmp;
	while(*env)
	{
		printf("%s == ", (*env)->key);
		printf("%s\n", (*env)->value);
		(*env) = (*env)->next;
	}
	exit(1);
}