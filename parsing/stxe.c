
# include "../execution/minishell.h"

void    stxe(t_tokens *to)
{
	// t_tokens *tmp;

	// tmp = to;
	while(to)
	{
		if ((to->type == 0 || to->type == 1 || to->type == 2 || to->type == 3 || to->type == 8) && (!to->next)) 
		{
			ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
			break;
		}
		else if (to->type == 3 && to->next->type != 4)
	   	{
			write(2, "syntax error near unexpected token `", 37);	
			ft_putstr_fd(ft_strjoin(to->next->cont, "\'\n"), 2);
			break;
	   	} 
		to = to->next;                                                                               
	}
	//to = tmp;
}