/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:09:19 by juan-aga          #+#    #+#             */
/*   Updated: 2023/06/07 10:40:46 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_export_check(char **str, t_ms *ms, int i, int j);
static void	ft_export_add(char *str, t_ms *ms, int diff);

int	valid_export_name(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (0);
	i++;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	ft_export(char **str, t_ms *ms)
{
	int			i;
	int			j;
	t_envlst	*tmp;

	tmp = ms->exp;
	i = 0;
	j = 0;
	if (!str[0])
	{
		ft_envlst_short(&ms->exp);
		while (tmp)
		{
			printf("declare -x %s", tmp->var);
			if (tmp->value)
				printf("=\"%s\"", tmp->value);
			printf("\n");
			tmp = tmp->next;
		}
	}
	else
		ft_export_check(str, ms, i, j);
}

static void	ft_export_check(char **str, t_ms *ms, int i, int j)
{
	t_envlst	*tmp;
	char		*var;

	while (str[i])
	{
		j = 0;
		while (str[i][j] && str[i][j] != '=')
			j++;
		var = ft_calloc(sizeof(char), j + 2);
		ft_strlcpy(var, str[i], j + 1);
		tmp = ft_getenv(var, ms->exp);
		if (!tmp && valid_export_name(str[i]))
			ft_export_add(str[i], ms, str[i][j] - '=');
		else if (valid_export_name(str[i]))
		{
			free(tmp->value);
			tmp->value = ft_strdup(&str[i][j + 1]);
			ft_export_to_env(str[i], ms->envlst);
		}
		else
			printf("minishell: export: `%s': not a valid identifier\n", str[i]);
		free(var);
		i++;
	}
}

static void	ft_export_add(char *str, t_ms *ms, int diff)
{
	if (str[0] == '\0')
		return ;
	if (!ms->exp && !ms->envlst)
	{
		ms->exp = ft_envlstnew(str);
		if (!diff)
			ms->envlst = ft_envlstnew(str);
	}
	else
	{
		ft_envlstadd_back(&ms->exp, ft_envlstnew(str));
		if (!diff)
			ft_envlstadd_back(&ms->envlst, ft_envlstnew(str));
	}
}

void	ft_export_to_env(char *str, t_envlst *envlst)
{
	t_envlst	*tmp;
	int			i;

	i = 0;
	tmp = envlst;
	if (!str)
		return ;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] != '=')
		return ;
	while (tmp)
	{
		if (!ft_strncmp(str, tmp->var, i) && !tmp->var[i])
		{
			tmp = ft_envlst_fill(tmp, str);
			return ;
		}
		tmp = tmp->next;
	}
	ft_envlstadd_back(&envlst, ft_envlstnew(str));
}
