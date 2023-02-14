#include "libft.h"
#include "minishell.h"

void	ft_pruebas(char *str, t_ms *ms)
{
	if (!ft_strncmp("env", str, 3))
	{
		ft_env(ms);
		ms->exit_status = 0;
	}
	else if (!ft_strncmp("export", str, 6))
	{
		ft_export(&str[7], ms);
		ms->exit_status = 0;
	}
	else if (!ft_strncmp("unset", str, 5))
	{
		ft_unset(&str[6], ms);
		ms->exit_status = 0;
	}
	else if (!ft_strncmp("exit", str, 4))
		ms->exit = 0;
	else
		ms->exit_status = 1;
}