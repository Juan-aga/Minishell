/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-aga <juan_aga@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:09:33 by juan-aga          #+#    #+#             */
/*   Updated: 2023/06/05 16:09:35 by juan-aga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "fractol_utils.h"
#include <stdio.h>

void	ft_dup(int in, int out)
{
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
}

void	ft_close_pipe(t_ms *ms)
{
	int	i;

	i = 0;
	while (i < (ms->num_com * 2 - 1))
	{
		close(ms->pipe[i]);
		i++;
	}
}

void	ft_get_path(t_ms *ms, t_cmdlst *tmp)
{
	int	i;

	i = 0;
	if (!access(tmp->arg[i], F_OK))
	{
		tmp->path = tmp->arg[i];
		return ;
	}
	if (!ms->path || tmp->arg[0][0] == '\0')
		return ;
	while (ms->path[i])
	{
		tmp->path = ft_strjoin_va("%s/%s", ms->path[i], tmp->arg[0]);
		if (!access(tmp->path, F_OK))
		{
			return ;
		}
		free(tmp->path);
		i++;
	}
	tmp->path = NULL;
}

void	ft_free_fork(t_ms *ms)
{
	lexer_free(ms->lexer);
	free(ms->pipe);
	if (ms->path)
		ft_free_array(ms->path, 0);
	ft_free_cmdlst(ms);
	ft_free(ms);
}
