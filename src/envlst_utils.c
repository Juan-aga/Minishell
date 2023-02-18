#include "minishell.h"
#include "libft.h"

t_envlst	*ft_copy_env(char **env)
{
	t_envlst	*new;
	int			i;

	i = 0;
	new = NULL;
	while (env[i])
	{
		if (i == 0)
			new = ft_envlstnew(env[i]);
		else
			ft_envlstadd_back(&new, ft_envlstnew(env[i]));
		i++;
	}
	return (new);
}
