#include "../execution/minishell.h"

int qoutesordlr(t_tokens *token)
{
	int i = 0;
	while (token->cont[i])
	{
		if (token->cont[i] == '\'' || token->cont[i] == '\"')
			return (1);
		if (token->cont[i] == '$' || token->cont[i] == '~')
			return (2);
		i++;
	}
	return(0);
	
}
char *expenv(char *str, t_env *env)
{
	t_env *rmp = env;
	while(env)
	{
		if (ft_strcmp(str, env->key) == 0)
			return (ft_strdup(env->value));
		env = env->next;
	}
	env = rmp;
	return (ft_strdup(""));
}

char    *expand_tokens(t_tokens *token, t_env *env)
{
	int i = 0;
	char *str = NULL;
	char *s = NULL;
	int j;
	extern int stx;
	char *strr = NULL; 
	while(token->cont[i])
	{
		if (token->cont[0] == '~' && token->cont[1] == '\0')
		{
			//i++;
			str = ft_strjoin(str, expenv("HOME", env));
		}
		else if(token->cont[i] == '$' &&  token->cont[i + 1] == '?' && lexer_openqts(token->cont, i) != 2)
		{
			//i++;
			str = ft_strjoin(str, ft_itoa(stx));
		}
		else if(token->cont[i] == '$' && lexer_openqts(token->cont, i) != 2)
		{
			j = i + 1;
			i = j;
			if (!(ft_isalnum(token->cont[i])))
				str = ft_chrjoin(str, token->cont[i - 1]);
			else 
			{
				while (i)
				{
					if (token->cont[i] == '\0' || !(ft_isalnum(token->cont[i])))
					{
						s = ft_substr(token->cont, j , (i - j));
						str = ft_strjoin(str, expenv(s, env));
						i--;
						break;
					}
					i++;
				}
			}
		}
		else if (lexer_openqts(token->cont , i) == 0 && token->cont[i] != '\'' && token->cont[i] != '\"')
			str = ft_chrjoin(str, token->cont[i]);
		else if (lexer_openqts(token->cont, i) == 1 && token->cont[i] == '\'')
			str = ft_chrjoin(str, token->cont[i]);
		else if (lexer_openqts(token->cont, i) == 2 && token->cont[i] == '\"')
			str = ft_chrjoin(str, token->cont[i]);
		else if (token->cont[i] != '\"' && token->cont[i] != '\'')
 			str = ft_chrjoin(str, token->cont[i]);
		i++;
	}
	if (str && str[0] == '\0' && (token->perv->type == 6 || token->perv->type == 7 || token->perv->type == 8))
	{
		ft_putstr_fd(ft_strjoin(token->cont, ": ") , 2);
		ft_putstr_fd("ambiguous redirect\n", 2);
		stx = 1;
	}
	return (str);
}

void    do_expand_tokens(t_tokens **tokens, t_env *env)
{
	t_tokens *tmp;
	char	*str;

	tmp = *tokens;
	while (*tokens)
	{
		if (qoutesordlr(*tokens))
		{
			str = expand_tokens(*tokens, env);
			free((*tokens)->cont);
			(*tokens)->cont = str;
		}
		*tokens = (*tokens)->next;
	}
	*tokens = tmp;
}


