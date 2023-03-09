#include "ft_printf.h"
#include "minishell.h"

extern t_ms	*g_ms;

/* the strange "\b\b  \b\b" is to delete the \^ token that CTRL+\ prints */
void	ft_sigint(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("\n%s", g_ms->prompt);
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
		signal(SIGINT, ft_sigint_proc);
	}
	else if (sig == SIGQUIT)
	{
		if (!kill(g_ms->pid, SIGTERM))
		{
			ft_printf("\n[%d]+\tStopped\t\t", g_ms->pid);
			if (g_ms->cmdlst && g_ms->cmdlst->arg)
				while (g_ms->cmdlst->arg[++i])
					ft_printf("%s ", g_ms->cmdlst->arg[i]);
			ft_printf("\n");
		}
	}
}
