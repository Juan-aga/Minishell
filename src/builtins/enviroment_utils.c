/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:11:01 by juan-aga          #+#    #+#             */
/*   Updated: 2023/06/07 10:40:39 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envlst	*ft_getenv(char *str, t_envlst *lst)
{
	t_envlst	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp)
	{
		if (!ft_strncmp(str, tmp->var, 100))
			break ;
		tmp = tmp->next;
	}
	if (tmp)
		return (tmp);
	return (NULL);
}

void	ft_shlvl_update(t_ms *ms)
{
	t_envlst	*tmp;
	char		**str;
	int			lvl;

	tmp = ft_getenv("SHLVL", ms->exp);
	str = ft_calloc(sizeof(char *), 4);
	lvl = 1;
	if (ms->exp && tmp && tmp->value)
		lvl = ft_atoi(tmp->value) + 1;
	str[0] = ft_strjoin_va("SHLVL=%i", lvl);
	ft_export(str, ms);
	free (str[0]);
	if (!ms->env)
	{
		str[0] = "OLDPWD\0";
		str[2] = getcwd(str[2], 0);
		str[1] = ft_strjoin_va("%s=%s", "PWD", str[2]);
		free(str[2]);
		str[2] = NULL;
		ft_export(str, ms);
		free(str[1]);
	}
	free(str);
}
