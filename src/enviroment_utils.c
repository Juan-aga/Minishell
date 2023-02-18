#include "libft.h"
#include "minishell.h"
#include "fractol_utils.h"

char	*ft_getenv(char *str, t_ms *ms)
{
	int		i;
	char	*tmp;

	i = 0;
	i = ft_check_env(str, ms, 'G');
	if (i < 0)
		return (NULL);
	if (i)
	{
		i -= 1;
		tmp = ft_strchr(ms->env[i], '=') + 1;
	}
	else
		return (NULL);
	return (tmp);
}

void	ft_shlvl_update(t_ms *ms)
{
	char	*tmp;
	int		lvl;

	tmp = ft_getenv("SHLVL", ms);
	lvl = ft_atoi(tmp) + 1;
	tmp = ft_strjoin_va("SHLVL=%i", lvl);
	ft_export(tmp, ms);
	free (tmp);
}
