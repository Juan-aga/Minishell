#include "libft.h"
#include "minishell.h"
#include <stdio.h>

static void	ft_export_check(char **str, t_ms *ms, int i, int j);
static void	ft_export_add(char *str, t_ms *ms, int diff);

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
		tmp = ft_getenv(var, ms);
		if (!tmp)
			ft_export_add(str[i], ms, str[i][j] - '=');
		else
		{
			free(tmp->value);
			tmp->value = ft_strdup(&str[i][j + 1]);
			ft_export_to_env(str[i], ms->envlst);
		}
		free(var);
		i++;
	}
}

static void	ft_export_add(char *str, t_ms *ms, int diff)
{
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
			break ;
		}
		tmp = tmp->next;
	}
	return ;
}
