#include "libft.h"
#include "minishell.h"
#include "fractol_utils.h"

char	**ft_copy_array(char **src, int add)
{
	int		i;
	char	**dest;

	i = 0;
	while (src[i])
		i++;
	dest = ft_calloc(sizeof(char *), i + 1 + add);
	if (!dest)
		return (NULL);
	i = 0;
	while (src[i])
	{
		dest[i] = ft_strdup(src[i]);
		if (!dest[i])
		{
			ft_free_array(dest, i);
			return (NULL);
		}
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

void	ft_free_array(char **str, int i)
{
	while (i >= 0)
	{
		free(str[i]);
		i--;
	}
	free(str);
}

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
