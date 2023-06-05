/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdlst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-aga <juan_aga@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:10:03 by juan-aga          #+#    #+#             */
/*   Updated: 2023/06/05 16:10:05 by juan-aga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_printf.h"
#include "libft.h"

t_cmdlst	*ft_cmdlstnew(void)
{
	t_cmdlst	*cmdlst;

	cmdlst = (t_cmdlst *) ft_calloc(1, sizeof(t_cmdlst));
	if (!cmdlst)
		return (NULL);
	cmdlst->path = NULL;
	cmdlst->arg = NULL;
	cmdlst->fd_in_file = NULL;
	cmdlst->fd_out_file = NULL;
	cmdlst->fd_in = 0;
	cmdlst->fd_out = 1;
	cmdlst->append = 0;
	cmdlst->next = NULL;
	cmdlst->prev = NULL;
	return (cmdlst);
}

void	ft_cmdlstadd_back(t_cmdlst **cmdlst, t_cmdlst *add)
{
	t_cmdlst	*last;

	if (!cmdlst || !add)
		return ;
	if (!cmdlst)
	{
		*cmdlst = add;
		return ;
	}
	last = ft_cmdlstlast(*cmdlst);
	last->next = add;
	add->prev = last;
}

t_cmdlst	*ft_cmdlstlast(t_cmdlst *cmdlst)
{
	t_cmdlst	*last;

	last = cmdlst;
	if (cmdlst)
	{
		while (last->next)
		last = last->next;
	}
	return (last);
}

void	ft_free_cmdlst(t_ms	*ms)
{
	t_cmdlst	*tmp;
	t_cmdlst	*cmdlst;

	cmdlst = ms->cmdlst;
	while (cmdlst)
	{
		tmp = cmdlst->next;
		if (cmdlst->path)
			free(cmdlst->path);
		if (cmdlst->arg)
			ft_free_array(cmdlst->arg, 0);
		free(cmdlst);
		cmdlst = tmp;
	}
	ms->cmdlst = 0;
}
