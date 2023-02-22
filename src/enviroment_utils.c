#include "libft.h"
#include "minishell.h"
#include "fractol_utils.h"

char	*ft_getenv(char *str, t_ms *ms)
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
		return (&tmp->value[0]);
	return (NULL);
}

void	ft_shlvl_update(t_ms *ms)
{
	char	*tmp;
	int		lvl;

	tmp = ft_getenv("SHLVL", ms);
	lvl = ft_atoi(tmp) + 1;
	tmp = ft_strjoin_va("SHLVL=%i", lvl);
	ft_export_to_env(tmp, ms->envlst);
	ft_export_to_env(tmp, ms->exp);
	free (tmp);
}
