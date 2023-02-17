#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <sys/wait.h>

static int	ft_childs_pip(t_ms *ms, t_cmdlst *tmp);
static void	ft_childs_exe(t_ms *ms, t_cmdlst *tmp);
static void	ft_child_redir_file(t_ms *ms, t_cmdlst *tmp);
static void	ft_accept_redirections(t_ms *ms, t_cmdlst *tmp);

void	ft_exec(t_ms *ms)
{
	t_cmdlst	*tmp;
	char		*path;

	path = ft_getenv("PATH", ms);
	ms->path = ft_split(path, ':');
	ms->exe = 0;
	tmp = ms->cmdlst;
	ms->pipe = ft_calloc(sizeof(int), ms->num_com + 1);
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
	free(ms->path);
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
		{
			ft_putstr_fd(" No such file or directory\n", 2);
			exit(-1);
		}
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
	{
		ft_putstr_fd(": command not found\n", 2);
		ft_free_array(tmp->arg, 0);
		exit(-1);
	}
	execve(tmp->path, tmp->arg, ms->env);
}

static void	ft_accept_redirections(t_ms *ms, t_cmdlst *tmp)
{
	if (!ft_strncmp("env", tmp->arg[0], 4))
	{
		ft_env(ms);
		exit (0);
	}
	else if (!ft_strncmp("pwd", tmp->arg[0], 4))
	{
		ft_pwd(ms);
		exit (0);
	}
	else if (!ft_strncmp("echo", tmp->arg[0], 5))
	{	
		exit (0);
	}
}
