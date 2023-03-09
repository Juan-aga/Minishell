#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <sys/wait.h>

static int	ft_childs_pip(t_ms *ms, t_cmdlst *tmp);
static void	ft_childs_exe(t_ms *ms, t_cmdlst *tmp);
static void	ft_child_redir_file(t_ms *ms, t_cmdlst *tmp);
static void	ft_exec_init(t_ms *ms);

void	ft_exec(t_ms *ms)
{
	t_cmdlst	*tmp;

	ft_exec_init(ms);
	tmp = ms->cmdlst;
	ms->pipe = ft_calloc(sizeof(int), ms->num_com * 2 + 1);
	while (ms->exe < ms->num_com)
	{
		pipe(ms->pipe + 2 * ms->exe);
		ms->exe += 1;
	}
	ms->exe = 0;
	while (tmp)
	{
		ms->exit_status = ft_childs_pip(ms, tmp);
		ms->exe += 1;
		tmp = tmp->next;
		wait(NULL);
		close(ms->pipe[2 * ms->exe - 2 + 1]);
	}
	ft_close_pipe(ms);
	free(ms->pipe);
	if (ms->path)
		ft_free_array(ms->path, 0);
}

static void	ft_exec_init(t_ms *ms)
{
	t_envlst	*tmp;

	tmp = ft_getenv("PATH", ms->exp);
	if (tmp)
		ms->path = ft_split(tmp->value, ':');
	else
		ms->path = NULL;
	ms->exe = 0;
}

static int	ft_childs_pip(t_ms *ms, t_cmdlst *tmp)
{
	pid_t	pros;
	int		status;

	status = ft_is_builtin(ms, tmp);
	if (status)
		return (ms->exit_status);
	pros = fork();
	if (!pros)
	{
		ft_child_redir_file(ms, tmp);
		ft_childs_exe(ms, tmp);
		exit(-1);
	}
	waitpid(pros, &status, 0);
	if (status)
		return (127);
	return (0);
}

static void	ft_child_redir_file(t_ms *ms, t_cmdlst *tmp)
{
	if (tmp->fd_in_file)
	{
		if (tmp->fd_in < 0)
			ft_error_file(tmp->fd_in_file, \
				": No such file or directory\n", ms);
		ms->pipe[2 * ms->exe] = tmp->fd_in;
	}
	if (tmp->fd_out_file)
		ms->pipe[2 * ms->exe + 1] = tmp->fd_out;
	else if (!tmp->next)
		ms->pipe[2 * ms->exe + 1] = tmp->fd_out;
	if (!ms->exe)
		ft_dup(tmp->fd_in, ms->pipe[2 * ms->exe + 1]);
	else
		ft_dup(ms->pipe[2 * ms->exe - 2], ms->pipe[2 * ms->exe + 1]);
}

static void	ft_childs_exe(t_ms *ms, t_cmdlst *tmp)
{
	ft_close_pipe(ms);
	ft_accept_redirections(ms, tmp);
	close(ms->pipe[2 * ms->exe - 2]);
	ft_get_path(ms, tmp);
	if (!tmp->path)
		ft_error_exe(tmp->arg, ": command not found\n", ms);
	ft_envlst_to_env(ms);
	execve(tmp->path, tmp->arg, ms->env);
	ft_free_array(ms->env, 0);
}
