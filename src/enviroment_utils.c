#include "libft.h"
#include "minishell.h"
#include "fractol_utils.h"
#include <stdio.h>

t_envlst	*ft_getenv(char *str, t_envlst *lst)
{
	t_envlst	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp != NULL)
	{
		if (!ft_strncmp(str, tmp->var, 100))
			break ;
		tmp = tmp->next;
	}
	if (tmp)
		return (tmp);
	return (NULL);
}

void	ft_shlvl_update(t_ms *ms)
{
	t_envlst	*tmp;
	int			lvl;

	tmp = ft_getenv("SHLVL", ms->exp);
	lvl = ft_atoi(tmp->value) + 1;
	free(tmp->value);
	tmp->value = ft_itoa(lvl);
	tmp = ft_getenv("SHLVL", ms->envlst);
	free(tmp->value);
	tmp->value = ft_itoa(lvl);
}
