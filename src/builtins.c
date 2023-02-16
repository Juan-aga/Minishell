#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "fractol_utils.h"

static void	ft_cd_error(char *str, t_ms *ms);

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

	if (!str)
	{
		i = chdir(ft_getenv("HOME", ms));
		if (i)
			ft_putstr_fd("minishell: cd: HOME: not set\n", 2);
		return ;
	}
	tmp = NULL;
	tmp = getcwd(tmp, 1000);
	dir = ft_strjoin_va("%s/%s", tmp, str);
	free(tmp);
	i = chdir(dir);
	if (i)
		i = chdir(str);
	if (i)
		ft_cd_error(str, ms);
	else
		ms->exit_status = 0;
	free(dir);
}

static void	ft_cd_error(char *str, t_ms *ms)
{
	char	*tmp;

	tmp = ft_strjoin_va(
		"minishell: cd: %s: No such file or directory\n", str);
	ft_putstr_fd(tmp, 2);
	ms->exit_status = 1;
	free(tmp);
}
