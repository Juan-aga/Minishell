#include "libft.h"
#include "minishell.h"
#include "fractol_utils.h"

t_envlst	*ft_getenv(char *str, t_ms *ms)
{
	t_envlst	*tmp;

	if (!ms->exp)
		return (NULL);
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
	char		*str[3];
	int			lvl;

	tmp = ft_getenv("SHLVL", ms);
	lvl = 1;
	if (tmp)
		lvl = ft_atoi(tmp->value) + 1;
	str[0] = ft_strjoin_va("SHLVL=%i", lvl);
	ft_export_to_env(str[0], ms->envlst);
	ft_export_to_env(str[0], ms->exp);
	free (str[0]);
	if (!ms->env[0])
	{
		str[0] = "OLDPWD\0";
		str[2] = NULL;
		str[2] = getcwd(str[2], 1000);
		str[1] = ft_strjoin_va("%s=%s", "PWD", str[2]);
		free(str[2]);
		str[2] = NULL;
		ft_export(str, ms);
		free(str[1]);
	}
}
