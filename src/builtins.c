#include "minishell.h"
#include "ft_printf.h"
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

void	ft_exit_ms(t_ms *ms)
{
	ft_putstr_fd("exit\n", 2);
	ms->exit = 0;
}

void	ft_pwd(t_ms *ms)
{
	char	*dir;

	(void) ms;
	dir = NULL;
	dir = getcwd(dir, 0);
	ft_printf("%s\n", dir);
	free(dir);
}

void	ft_echo(char **str)
{
	int	nl;
	int	i;

	nl = 1;
	i = 0;
	if (str[i])
	{
		if (!ft_strncmp("-n", str[i], 4))
		{
			nl = 0;
			i++;
		}
	}
	while (str[i])
	{
		printf("%s", str[i]);
		if (str[++i])
			printf(" ");
	}
	if (nl)
		printf("\n");
}
