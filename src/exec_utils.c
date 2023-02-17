#include "minishell.h"
#include "fractol_utils.h"
#include <stdio.h>

void	ft_dup(int in, int out)
{
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
}

void	ft_close_pipe(t_ms *ms)
{
	int	i;

	i = 0;
	while (i < (ms->num_com * 2 - 1))
	{
		close(ms->pipe[i]);
		i++;
	}
}

void	ft_get_path(t_ms *ms, t_cmdlst *tmp)
{
	int	i;

	i = 0;
	if (!access(tmp->arg[i], F_OK))
	{
		tmp->path = tmp->arg[i];
		return ;
	}
	while (ms->path[i])
	{
		tmp->path = ft_strjoin_va("%s/%s", ms->path[i], tmp->arg[0]);
		if (!access(tmp->path, F_OK))
		{
			return ;
		}
		free(tmp->path);
		i++;
	}
	tmp->path = NULL;
}