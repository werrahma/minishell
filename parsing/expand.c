#include "../execution/minishell.h"

int qoutesordlr(t_tokens *token)
{
	int i = 0;
	while (token->cont[i])
	{
		if (token->cont[i] == '\'' || token->cont[i] == '\"')
			return (1);
		if (token->cont[i] == '$')
			return (2);
		i++;
	}
	return(0);
	
}
char *expenv(char *str, t_env *env)
{
	while(env)
	{
		if (ft_strcmp(str, env->key) == 0)
			return (env->value);
		env = env->next;
	}
	return (ft_strdup(""));
}

void    expand_tokens(t_tokens *token, t_env *env)
{
	int i = 0;
	char *str = NULL;
	char *s = NULL;
	int j;

	while(token->cont[i])
	{
		if(token->cont[i] == '$')
		{
			j = i + 1;
			break;
		}
		else
			str = ft_chrjoin(str, token->cont[i]);
		i++;
	}
	i = j;
	while (token->cont[i])
	{
		if(!(ft_isalnum(token->cont[i])))
			break;
		i++;
	}
	s = ft_substr(token->cont, j , i - j);
	str = ft_strjoin(str, expenv(s, env));
	printf("**%s\n", str);
}
void    do_expand_tokens(t_tokens **tokens, t_env *env)
{
	t_tokens *tmp;

	tmp = *tokens;

	while (*tokens)
	{
		if (qoutesordlr(*tokens) == 2)
		{
			expand_tokens(*tokens, env);
		}
		*tokens = (*tokens)->next;
	}
	*tokens = tmp;
}


