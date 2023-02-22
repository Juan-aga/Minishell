#include "minishell.h"
#include "libft.h"

t_envlst	*ft_copy_env(char **env)
{
	t_envlst	*new;
	int			i;

	i = 0;
	new = NULL;
	if (!env)
		return (NULL);
	while (env[i])
	{
		if (i == 0)
			new = ft_envlstnew(env[i]);
		else
			ft_envlstadd_back(&new, ft_envlstnew(env[i]));
		i++;
	}
	return (new);
}

void	ft_envlst_short(t_envlst **lst)
{
	int			diff;
	char		*change;
	t_envlst	*tmp;

	tmp = *lst;
	if (!*lst)
		return ;
	while (tmp->next)
	{
		diff = ft_strncmp(tmp->var, tmp->next->var, 100);
		if (diff > 0)
		{
			change = tmp->var;
			tmp->var = tmp->next->var;
			tmp->next->var = change;
			change = tmp->value;
			tmp->value = tmp->next->value;
			tmp->next->value = change;
			tmp = *lst;
		}
		else
			tmp = tmp->next;
	}
}
