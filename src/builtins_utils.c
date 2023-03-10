#include "minishell.h"
#include "libft.h"
#include "stdio.h"

static int	ft_no_redirections(t_ms *ms, t_cmdlst *tmp);

int	ft_is_builtin(t_ms *ms, t_cmdlst *tmp)
{
	if (ft_no_redirections(ms, tmp))
		return (1);
	if (!tmp || !tmp->arg || !tmp->arg[0])
		return (0);
	if (!ft_strncmp("cd", tmp->arg[0], 3))
	{
		if (ms->num_com == 1)
			ft_cd(tmp->arg[1], ms);
		return (1);
	}	
	return (0);
}

static int	ft_no_redirections(t_ms *ms, t_cmdlst *tmp)
{
	if (!tmp || !tmp->arg)
		return (0);
	if (!ft_strncmp("export", tmp->arg[0], 7))
	{
		if (!tmp->arg[1])
			return (0);
		if (ms->num_com == 1)
			ft_export(&tmp->arg[1], ms);
		ms->exit_status = 0;
		return (1);
	}
	else if (!ft_strncmp("unset", tmp->arg[0], 6))
	{
		if (ms->num_com == 1)
			ft_unset(&tmp->arg[1], ms);
		ms->exit_status = 0;
		return (1);
	}
	else if (!ft_strncmp("exit", tmp->arg[0], 5))
	{
		if (ms->num_com == 1)
			ft_exit_ms(ms);
		return (1);
	}
	return (0);
}

void	ft_accept_redirections(t_ms *ms, t_cmdlst *tmp)
{
	t_envlst	*get;

	if (!tmp || !tmp->arg || !tmp->arg[0])
		return ;
	if (!ft_strncmp("env", tmp->arg[0], 4))
		ft_env(ms);
	else if (!ft_strncmp("pwd", tmp->arg[0], 4))
		ft_pwd(ms);
	else if (!ft_strncmp("echo", tmp->arg[0], 5))
		ft_echo(&tmp->arg[1]);
	else if (!ft_strncmp("getenv", tmp->arg[0], 7))
	{
		if (!tmp->arg[1])
			exit (0);
		get = ft_getenv(tmp->arg[1], ms->exp);
		if (get)
			printf("%s\n", get->value);
	}
	else if (!ft_strncmp("export", tmp->arg[0], 7))
		ft_export(&tmp->arg[1], ms);
	else
		return ;
	ft_free_fork(ms);
	exit (0);
}
