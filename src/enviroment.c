#include "libft.h"
#include "minishell.h"
#include <stdio.h>

static void	ft_free_array(char **str, int i);
static void	ft_copy_array(char **dest, char **src);

void	ft_get_env(t_ms *ms, char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	ms->env = ft_calloc(sizeof(char *), i + 1);
	ft_copy_array(ms->env, env);
}

static void	ft_free_array(char **str, int i)
{
	while (i >= 0)
	{
		free(str[i]);
		i--;
	}
	free(str);
}

static void	ft_copy_array(char **dest, char **src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = ft_strdup(src[i]);
		if (!dest[i])
		{
			ft_free_array(dest, i);
			return ;
		}
		i++;
	}
	dest[i] = NULL;
}

void	ft_export(char *str, t_ms *ms)
{
	int		i;
	char	**tmp;

	i = 0;
	while (ms->env[i])
		i++;
	tmp = ft_calloc(sizeof(char *), i + 2);
	if (!tmp)
		return ;
	ft_copy_array(tmp, ms->env);
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
