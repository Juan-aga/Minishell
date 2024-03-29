/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:11:59 by juan-aga          #+#    #+#             */
/*   Updated: 2023/06/07 10:41:41 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envlst	*ft_envlstnew(char *str)
{
	t_envlst	*envlst;

	envlst = (t_envlst *) ft_calloc(1, sizeof(t_envlst));
	if (!envlst)
		return (NULL);
	envlst->var = NULL;
	envlst->value = NULL;
	envlst->next = NULL;
	envlst->prev = NULL;
	ft_envlst_fill(envlst, str);
	return (envlst);
}

void	ft_envlstadd_back(t_envlst **envlst, t_envlst *add)
{
	t_envlst	*last;

	if (!envlst || !add)
		return ;
	if (!envlst)
	{
		*envlst = add;
		return ;
	}
	last = ft_envlstlast(*envlst);
	last->next = add;
	add->prev = last;
}

t_envlst	*ft_envlstlast(t_envlst *envlst)
{
	t_envlst	*last;

	last = envlst;
	if (envlst)
	{
		while (last->next)
			last = last->next;
	}
	return (last);
}

void	ft_free_envlst(t_envlst *envlst)
{
	t_envlst	*tmp;

	while (envlst)
	{
		tmp = envlst->next;
		free(envlst->var);
		if (envlst->value)
			free(envlst->value);
		free(envlst);
		envlst = tmp;
	}
}

t_envlst	*ft_envlst_fill(t_envlst *envlst, char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (envlst->var)
		free(envlst->var);
	envlst->var = ft_calloc(sizeof(char), i + 2);
	ft_strlcpy(envlst->var, str, i + 1);
	if (envlst->value)
		free(envlst->value);
	if (str[i] == '=')
		envlst->value = ft_strdup(&str[i + 1]);
	else
		envlst->value = NULL;
	return (envlst);
}
