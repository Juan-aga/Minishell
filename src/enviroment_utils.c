#include "libft.h"
#include "minishell.h"
#include "fractol_utils.h"

t_envlst	*ft_getenv(char *str, t_ms *ms)
{
	t_envlst	*tmp;

	tmp = ms->exp;
	while (tmp)
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
	char		*str;
	int			lvl;

	tmp = ft_getenv("SHLVL", ms);
	lvl = 1;
	if (tmp)
		lvl = ft_atoi(tmp->value) + 1;
	str = ft_strjoin_va("SHLVL=%i", lvl);
	ft_export_to_env(str, ms->envlst);
	ft_export_to_env(str, ms->exp);
	free (str);
}
