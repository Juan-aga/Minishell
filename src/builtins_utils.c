#include "minishell.h"
#include "libft.h"

static int	ft_no_redirections(t_ms *ms, t_cmdlst *tmp);

int	ft_is_builtin(t_ms *ms, t_cmdlst *tmp)
{
	if (ft_no_redirections(ms, tmp))
		return (1);
	if (!ft_strncmp("cd", tmp->arg[0], 3))
	{
		if (tmp->arg[2] && tmp->arg[1])
		{
			ft_putstr_fd("minishell: cd: too many argumets\n", 2);
			ms->exit_status = 1;
		}
		else if (ms->num_com == 1)
			ft_cd(tmp->arg[1], ms);
		return (1);
	}	
	return (0);
}

static int	ft_no_redirections(t_ms *ms, t_cmdlst *tmp)
{
	if (!ft_strncmp("export", tmp->arg[0], 7))
	{
		if (ms->num_com == 1)
			ft_export(tmp->arg[1], ms);
		ms->exit_status = 0;
		return (1);
	}
	else if (!ft_strncmp("unset", tmp->arg[0], 6))
	{
		if (ms->num_com == 1)
			ft_unset(tmp->arg[1], ms);
		ms->exit_status = 0;
		return (1);
	}
	else if (!ft_strncmp("exit", tmp->arg[0], 5))
	{
		if (ms->num_com == 1)
			ft_exit(ms);
		return (1);
	}
	return (0);
}
