#include "libft.h"
#include "minishell.h"

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

void	ft_del_items_array(char **str, int del)
{
	int	i;

	i = 0;
	if (del < 1)
		return ;
	while (str[i] && i < del)
	{
		free(str[i]);
		i++;
	}
	free(str[i]);
	i = 0;
	while (str[i + del])
	{
		str[i] = ft_strdup(str[i + del]);
		free (str[i + del]);
		i++;
	}
	str[i] = str[i + del];
	free (str[i + del]);
}

void	ft_free_array(char **str, int i)
{
	if (!str)
		return ;
	if (!i)
	{
		while (str[i])
		{
			free(str[i]);
			i++;
		}
		free(str[i]);
	}
	else
	{
		while (i >= 0)
		{
			free(str[i]);
			i--;
		}
	}
	free(str);
}
