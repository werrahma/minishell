
#include "minishell.h"

void	ft_lstadd_back(t_tokens **lst, t_tokens *new)
{
	t_tokens	*tmp;

	tmp = ft_lstlast(*lst);
	if (!lst || !new)
		return ;
	if (*lst == NULL )
	{
		(*lst) = new;
		new->perv = NULL;
		return ;
	}	
	else
		ft_lstlast(*lst)->next = new;
	new->perv = tmp;
}

t_tokens	*ft_lstnew( char *content)
{
	t_tokens	*lst;

	lst = malloc(sizeof(t_tokens));
	if (!lst)
		return (NULL);
	lst->cont = content;
	lst->next = NULL;
	lst->perv = NULL;
	return (lst);
}

t_tokens	*ft_lstlast(t_tokens *lst)
{
	if (!lst)
		return (NULL);
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

char	*ft_chrjoin(char *dst, char c)
{
	char	*p;
	int		i;
	int		j;

	p = NULL;
	if (!dst && !c)
		return (NULL);
	if (!dst)
	{
		p = malloc(2);
		p[0] = c;
		p[1] = '\0';
		return (p);
	}
	p = ft_calloc((ft_strlen(dst) + 2), sizeof(char));
	if (!p)
		return (0);
	i = -1;
	while (dst[++i])
		p[i] = dst[i];
	p[i++] = c;
	p[i] = '\0';
	free(dst);
	return (p);
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	char	*ptr;

	i = 0;
	if (count && size > SIZE_MAX / count)
		return (NULL);
	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	while (i < count)
	{
		ptr[i] = '\0';
		i++;
	}
	return (ptr);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	size_t	i;
	size_t	len;
	char	*p;

	i = 0;
	len = ft_strlen(s1);
	p = (char *)malloc((len + 1) * sizeof(char));
	if (!p)
		return (NULL);
	while (i < len)
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
} 