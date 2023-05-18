#include "ft_printf.h"
#include "minishell.h"

extern t_ms	*g_ms;

/* the strange "\b\b  \b\b" is to delete the \^ token that CTRL+\ prints */
void	ft_sigint(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("  \n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_ms->exit_status = 127 + sig;
		signal(SIGINT, ft_sigint);
	}
	else if (sig == SIGQUIT)
		ft_printf("\b\b  \b\b");
}

void	ft_sigint_proc(int sig)
{
	int	i;

	i = -1;
	if (sig == SIGINT)
	{
		ft_printf("\n");
		g_ms->exit_status = 127 + sig;
		signal(SIGINT, ft_sigint_proc);
	}
	else if (sig == SIGQUIT)
	{
		if (!kill(g_ms->pid, SIGTERM))
		{
			g_ms->exit_status = 127 + sig;
			ft_printf("\n[%d]+\tStopped\t\t", g_ms->pid);
			if (g_ms->cmdlst && g_ms->cmdlst->arg)
				while (g_ms->cmdlst->arg[++i])
					ft_printf("%s ", g_ms->cmdlst->arg[i]);
			ft_printf("\n");
		}
	}
}
