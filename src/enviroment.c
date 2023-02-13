#include "libft.h"
#include "minishell.h"

static void	ft_free_array(char **str, int i);

void	ft_get_env(t_ms *ms, char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	ms->env = ft_calloc(sizeof(char *), i + 1);
	i = 0;
	while (env[i])
	{
		ms->env[i] = ft_strdup(env[i]);
		if (!ms->env[i])
		{
			ft_free_array(ms->env, i);
			return ;
		}
		i++;
	}
	ms->env[i] = NULL;
}

static void	ft_free_array(char **str, int i)
{
	while (i >= 0)
	{
		free(str[i]);
		i++;
	}
	free(str);
}
