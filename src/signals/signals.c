/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 18:23:38 by franmart          #+#    #+#             */
/*   Updated: 2023/10/01 17:02:10 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_ms	*g_ms;

/*	fix visual CTRL+ with termios.
 *	&= ~	: it's disable the attribute.
 *	ECHOCTL	: reference to CTRL char.
 *	TCSANOW	: change the attribute immediately.
 *	termios C_LFLAG	: refers to local modes.
 */

void	ft_sigint(int sig)
{
	struct termios	prompt;

	if (sig == SIGINT)
	{
		ft_printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_ms->exit_status = 127 + sig;
		signal(SIGINT, ft_sigint);
	}
	tcgetattr(STDIN_FILENO, &prompt);
	prompt.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &prompt);
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

void	ft_signheredoc(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("\n");
		g_ms->exit_status = 127 + sig;
		exit(1);
	}
}
