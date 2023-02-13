#include "libft.h"
#include "minishell.h"
#include <stdio.h>

void	ft_export(char *str, t_ms *ms)
{
	int		i;
	char	**tmp;

	i = 0;
	i = ft_check_env(str, ms);
	if (i)
	{
		free(ms->env[i]);
		ms->env[i] = ft_strdup(str);
		return ;
	}
	while (ms->env[i])
		i++;
	tmp = ft_copy_array(ms->env, 1);
	if (!tmp)
		return ;
	tmp[i] = ft_strdup(str);
	tmp[i + 1] = NULL;
	ft_free_array(ms->env, i - 1);
	ms->env = tmp;
}

void	ft_env(t_ms *ms)
{
	int	i;

	i = 0;
	while (ms->env[i])
	{
		printf("%s\n", ms->env[i]);
		i++;
	}
}

int	ft_check_env(char *str, t_ms *ms)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[j] && str[j] != '=')
		j++;
	if (!str[j])
		return (0);
	while (ms->env[i])
	{
		if (!ft_strncmp(str, ms->env[i], j))
			return (i);
		i++;
	}
	return (0);
}
