#include "libft.h"
#include "minishell.h"
#include "stdio.h"
#include <fcntl.h>

void	ft_simpleparser(char *str, t_ms *ms);
void	ft_check_builtin(t_ms *ms, t_cmdlst *lst);
int		ft_fill_cmd(char *str, t_cmdlst *lst);
void	ft_run_builtin(t_ms *ms);
void	ft_run_builtin(t_ms *ns);

void	ft_pruebas(char *str, t_ms *ms)
{
	if (!str)
		return ;
	ft_simpleparser(str, ms);
	if (!ms->num_com)
		return ;

//	ft_check_builtin(ms, ms->cmdlst);
//	ft_run_builtin(ms);
	ft_exec(ms);
//	printf("status %i\n", ms->exit_status);
}

void	ft_check_builtin(t_ms *ms, t_cmdlst *lst)
{
	t_cmdlst	*tmp;

	tmp = lst;
	while (tmp)
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
		tmp = tmp->next;
	}
}

void	ft_run_builtin(t_ms *ms)
{
	t_cmdlst	*tmp;
	char		*env;

	tmp = ms->cmdlst;
	while (tmp)
	{
		if (!ft_strncmp("env", tmp->arg[0], 4))
		{
			ft_env(ms);
			ms->exit_status = 0;
		}
		else if (!ft_strncmp("export", tmp->arg[0], 7))
			ft_export(tmp->arg[1], ms);
		else if (!ft_strncmp("unset", tmp->arg[0], 6))
			ft_unset(tmp->arg[1], ms);
		else if (!ft_strncmp("exit", tmp->arg[0], 5))
			ft_exit(ms);
		else if (!ft_strncmp("getenv", tmp->arg[0], 7))
		{
			env = ft_getenv(tmp->arg[1], ms);
			printf("%s value is: %s\n", tmp->arg[1], env);
		}
		else if (!ft_strncmp("pwd", tmp->arg[0], 4))
			ft_pwd(ms);
		else if (!ft_strncmp("cd", tmp->arg[0], 3))
		{
			if (tmp->arg[2] && tmp->arg[1])
			{
				ft_putstr_fd("minishell: cd: too many argumets\n", 2);
				ms->exit_status = 1;
			}
			else
			ft_cd(tmp->arg[1], ms);
		}	
		tmp = tmp->next;
	}
}

void	ft_simpleparser(char *str, t_ms *ms)
{
	char		**split;
	int			i;
	int			error;
	t_cmdlst	*tmp;

	split = ft_split(str, '|');
	i = 0;
	error = 0;
	while (split[i] && !error)
	{
		if (i == 0)
		{
			tmp = ft_cmdlstnew();
			ms->cmdlst = tmp;
		}
		else
		{
			ft_cmdlstadd_back(&ms->cmdlst, ft_cmdlstnew());
			tmp = tmp->next;
		}
		ft_fill_cmd(split[i], tmp);
		i++;
	}
	ft_free_array(split, 0);
	if (error)
	{
		ft_free_cmdlst(ms->cmdlst);
		return ;
	}
	ms->num_com = i;
}

int	ft_fill_cmd(char *str, t_cmdlst *lst)
{
	char		**tmp;
	int			i;
	int			error;

	tmp = ft_split(str, ' ');
	i = 0;
	error = 0;
	while (tmp[i])
	{
		if (tmp[i][0] == '<')
		{
			lst->fd_in_file = tmp[i + 1];
			lst->fd_in = open(tmp[i + 1], O_RDONLY);
			ft_del_items_array(&tmp[i], 2);
		}
		else if (tmp[i][0] == '>')
		{
			lst->fd_out = open(tmp[i + 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (lst->fd_out < 0)
			{
				ft_putstr_fd("error out file", 2);
				error = 1;
				break ;
			}
			lst->fd_out_file = tmp[i + 1];
			ft_del_items_array(&tmp[i], 2);
		}
		i++;
	}
	lst->arg = ft_copy_array(tmp, 0);
	ft_free_array(tmp, 0);
	return (error);
}
