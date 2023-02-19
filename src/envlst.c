#include "minishell.h"
#include "libft.h"
#include <stdio.h>

t_envlst	*ft_envlstnew(char *str)
{
	t_envlst	*envlst;

	envlst = (t_envlst *) ft_calloc(1, sizeof(t_envlst));
	if (!envlst)
		return (NULL);
	envlst->var = NULL;
	envlst->value = NULL;
	envlst->next = NULL;
	ft_envlst_fill(envlst, str);
	return (envlst);
}

void	ft_envlstadd_back(t_envlst **envlst, t_envlst *add)
{
	t_envlst	*last;

	if (!envlst || !add)
		return ;
	if (!envlst)
	{
		*envlst = add;
		return ;
	}
	last = ft_envlstlast(*envlst);
	last->next = add;
}

t_envlst	*ft_envlstlast(t_envlst *envlst)
{
	t_envlst	*last;

	last = envlst;
	if (envlst)
	{
		while (last->next)
			last = last->next;
	}
	return (last);
}

void	ft_free_envlst(t_envlst *envlst)
{
	t_envlst	*tmp;

	while (envlst)
	{
		tmp = envlst->next;
		free(envlst->var);
		if (envlst->value)
			free(envlst->value);
		free(envlst);
		envlst = tmp;
	}
}

t_envlst	*ft_envlst_fill(t_envlst *envlst, char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (envlst->var)
		free(envlst->var);
	envlst->var = ft_calloc(sizeof(char), i + 2);
	ft_strlcpy(envlst->var, str, i + 1);
	if (envlst->value)
		free(envlst->value);
	if (str[i] == '=')
		envlst->value = ft_strdup(&str[i + 1]);
	else
		envlst->value = NULL;
	return (envlst);
}

void	ft_envlst_delete(char *str, t_envlst *lst)
{
	t_envlst	*del;
	t_envlst	*tmp;

	tmp = lst;
	while (tmp->next && ft_strncmp(tmp->next->var, str, 100))
		tmp = tmp->next;
	if (tmp->next || !ft_strncmp(tmp->var, str, 100))
	{
		del = tmp->next;
		tmp->next = tmp->next->next;
		free(del->var);
		free(del->value);
		free(del);
	}
	else if (!ft_strncmp(lst->var, str, 100))
	{
		del = lst;
		if (!lst->next)
			ft_free_envlst(lst);
		else
		{
			lst = lst->next;
			free(del->var);
			free(del->value);
			free(del);
		}
	}
}
