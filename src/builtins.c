#include "minishell.h"
#include "ft_printf.h"
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

void	ft_exit(t_ms *ms)
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
	exit(0);
}
