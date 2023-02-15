#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "fractol_utils.h"

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

void	ft_cd(char *str, t_ms *ms)
{
	char	*tmp;
	char	*dir;
	int		i;

	tmp = NULL;
	tmp = getcwd(tmp, 1000);
	dir = ft_strjoin_va("%s/%s", tmp, str);
	free(tmp);
	i = chdir(dir);
	if (i)
		i = chdir(str);
	if (i)
	{
		tmp = ft_strjoin_va(
				"-minishell: cd: %s: No such file or directory\n", str);
		ft_putstr_fd(tmp, 2);
		ms->exit_status = 1;
		free(tmp);
	}
	else
		ms->exit_status = 0;
	free(dir);
}
