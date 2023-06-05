/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-aga <juan_aga@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:12:22 by juan-aga          #+#    #+#             */
/*   Updated: 2023/06/05 16:12:23 by juan-aga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	ft_error_exe(char **arg, char *msg, t_ms *ms)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(arg[0], 2);
	ft_putstr_fd(msg, 2);
	ft_free_fork(ms);
	exit(-1);
}

void	ft_error_file(char *file, t_ms *ms)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(file, 2);
	if (access(file, F_OK))
		ft_putstr_fd(": No such file or directory\n", 2);
	else
		ft_putstr_fd(": Permission denied\n", 2);
	ft_free_fork(ms);
	exit(-1);
}
