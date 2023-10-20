/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:11:48 by juan-aga          #+#    #+#             */
/*   Updated: 2023/06/07 10:40:29 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_error_unset(char *str, int *err);

void	ft_unset(char **str, t_ms *ms)
{
	t_envlst	*tmp;
	int			i;
	int			err;

	i = 0;
	err = 0;
	if (!str)
		return ;
	while (str[i])
	{
		if (ft_strchr(str[i], '='))
			ft_error_unset(str[i], &err);
		else
		{
			tmp = ft_getenv(str[i], ms->exp);
			ft_envlst_del(&tmp);
			tmp = ft_getenv(str[i], ms->envlst);
			ft_envlst_del(&tmp);
		}
		i++;
	}
	ms->exit_status = err;
}

static void	ft_error_unset(char *str, int *err)
{
	char	*msg;

	msg = ft_strjoin("minishell: unset: \"%s\": not a valid identifier", str);
	ft_putstr_fd(msg, 2);
	*err = 1;
}

void	ft_env(t_ms *ms)
{
	t_envlst	*tmp;

	tmp = ms->envlst;
	while (tmp)
	{
		printf("%s=%s\n", tmp->var, tmp->value);
		tmp = tmp->next;
	}
}

int	ft_check_env(char *str, t_ms *ms, char c)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (!str)
		return (-1);
	while (str[j] && str[j] != '=')
		j++;
	if (str[j] != '=' && c == 'E')
		return (-1);
	while (ms->env[i - 1])
	{
		if (!ft_strncmp(str, ms->env[i - 1], j) && ms->env[i - 1][j] == '=')
			return (i);
		i++;
	}
	return (0);
}
