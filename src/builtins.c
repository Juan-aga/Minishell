#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void	ft_exit(t_ms *ms)
{
	ms->exit = 0;
}

void	ft_pwd(t_ms *ms)
{
	char	*dir;

	dir = NULL;
	dir = getcwd(dir, 1000);
	printf("%s\n", dir);
	free(dir);
	ms->exit_status = 0;
}
