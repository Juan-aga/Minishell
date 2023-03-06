#include "libft.h"
#include "ft_printf.h"
#include "minishell.h"
#include "stdio.h"
#include <fcntl.h>

void	ft_check_builtin(t_ms *ms, t_cmdlst *lst);
void	ft_run_builtin(t_ms *ms, t_cmdlst *cmds);

void	ft_pruebas(char *str, t_ms *ms)
{
	if (!str)
		return ;
	//ft_simpleparser(str, ms);
	if (!ms->num_com)
		return ;
	//ft_check_builtin(ms, ms->cmdlst);
	//ft_run_builtin(ms, ms->cmdlst);
	//ft_free_cmdlst(ms->cmdlst);
//	printf("status %i\n", ms->exit_status);
}

void	ft_check_builtin(t_ms *ms, t_cmdlst *lst)
{
	t_cmdlst	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (tmp->arg && tmp->arg[0])
		{
			if (!ft_strncmp("env", tmp->arg[0], 4))
				ms->num_com -= 1;
			else if (!ft_strncmp("export", tmp->arg[0], 7))
				ms->num_com -= 1;
			else if (!ft_strncmp("unset", tmp->arg[0], 6))
				ms->num_com -= 1;
			else if (!ft_strncmp("exit", tmp->arg[0], 5))
				ms->num_com -= 1;
			else if (!ft_strncmp("getenv", tmp->arg[0], 7))
				ms->num_com -= 1;
			else if (!ft_strncmp("pwd", tmp->arg[0], 4))
				ms->num_com -= 1;
			else if (!ft_strncmp("cd", tmp->arg[0], 3))
				ms->num_com -= 1;
		}
		tmp = tmp->next;
	}
}

void	ft_run_builtin(t_ms *ms, t_cmdlst *cmds)
{
	t_envlst	*env;

	while (cmds)
	{
		if (cmds->arg && cmds->arg[0])
		{
			if (!ft_strncmp("env", cmds->arg[0], 4))
			{
				ft_env(ms);
				ms->exit_status = 0;
			}
			else if (!ft_strncmp("export", cmds->arg[0], 7))
				ft_export(&cmds->arg[1], ms);
			else if (!ft_strncmp("unset", cmds->arg[0], 6))
				ft_unset(&cmds->arg[1], ms);
			else if (!ft_strncmp("exit", cmds->arg[0], 5))
				ft_exit(ms);
			else if (!ft_strncmp("getenv", cmds->arg[0], 7))
			{
				env = ft_getenv(cmds->arg[1], env);
				printf("%s value is: %s\n", cmds->arg[1], env->value);
			}
			else if (!ft_strncmp("pwd", cmds->arg[0], 4))
				ft_pwd(ms);
			else if (!ft_strncmp("cd", cmds->arg[0], 3))
			{
				if (cmds->arg[2] && cmds->arg[1])
				{
					ft_putstr_fd("minishell: cd: too many argumets\n", 2);
					ms->exit_status = 1;
				}
				else
					ft_cd(cmds->arg[1], ms);
			}
		}
		cmds = cmds->next;
	}
}
