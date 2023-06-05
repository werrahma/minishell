
# include "../execution/minishell.h"

void    stxe(t_tokens *to)
{
	// t_tokens *tmp;
	extern int stx;
	// tmp = to;
	while(to)
	{
		if ((to->type == 6 || to->type == 7 || to->type == 2 || to->type == 3 || to->type == 8) && (!to->next)) 
		{
			ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
			stx = 1;
			break;
		}
		else if (to->type == 3 && to->next->type != 4)
	   	{
			write(2, "syntax error near unexpected token `", 37);	
			ft_putstr_fd(ft_strjoin(to->next->cont, "\'\n"), 2);
			stx = 1;
			break;
	   	} 
		to = to->next;                                                                               
	}
	//to = tmp;
}

// void	ambiguous_stx(t_tokens *tokens, t_env *env)
// {
// 	t_tokens	*tmp;
// 	char		*st;

// 	tmp = tokens;

// 	while(tokens)
// 	{
// 		//st = expenv(tokens->next->cont, env);
// 		if ((tokens->type == 6 || tokens->type == 7 || tokens->type == 8))
// 		{
// 			st = expenv(tokens->next->cont, env);
// 			printf("=====%s\n", tokens->next->cont); 
// 			if (st[0] == '\0')
// 			{
// 				ft_putstr_fd(ft_strjoin(tokens->next->cont, ": ") , 2);
// 				ft_putstr_fd("ambiguous redirect\n", 2);
// 			}
// 		}
// 		tokens = tokens->next;
// 	}
// 	tokens = tmp;
// }