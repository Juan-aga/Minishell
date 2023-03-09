#include "ft_printf.h"
#include "minishell.h"

extern t_ms *ms;

/* the strange "\b\b  \b\b" is to delete the \^ token that CTRL+\ prints */
void	ft_sigint(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("\n%s", ms->prompt);
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
		if (!kill(ms->pid, SIGTERM))
		{
			ft_printf("\n[%d]+\tStopped\t\t", ms->pid);
			if (ms->cmdlst && ms->cmdlst->arg)
				while (ms->cmdlst->arg[++i])
					ft_printf("%s ", ms->cmdlst->arg[i]);
			ft_printf("\n");
		}
	}
}
