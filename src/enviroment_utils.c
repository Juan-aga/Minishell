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

void	ft_free_array(char **str, int i)
{
	while (i >= 0)
	{
		free(str[i]);
		i--;
	}
	free(str);
}