#include "libft.h"
#include "minishell.h"
#include "stdio.h"

void	ft_pruebas(char *str, t_ms *ms)
{
	char	*tmp;

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
	else if (!ft_strncmp("getenv", str, 6))
	{
		tmp = ft_getenv(&str[7], ms);
		if (!tmp)
			ms->exit_status = 1;
		else
		{
			printf("getenv of %s is: %s\n", &str[7], tmp);
			ms->exit_status = 0;
		}
	}
	else
		ms->exit_status = 1;
}
