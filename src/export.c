#include "libft.h"
#include "minishell.h"
#include <stdio.h>

static void	ft_export_check(char **str, t_ms *ms, int i, int j);
static void	ft_export_add(char *str, t_ms *ms, int dif);

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

	tmp = ms->exp;
	while (str[i])
	{
		j = 0;
		while (str[i][j] && str[i][j] != '=')
			j++;
		while (tmp)
		{
			if (!ft_strncmp(str[i], tmp->var, j) && !tmp->var[j])
			{
				tmp = ft_envlst_fill(tmp, str[i]);
				ft_export_to_env(str[i], ms->envlst);
				break ;
			}
			tmp = tmp->next;
		}
		if (!tmp)
			ft_export_add(str[i], ms, str[i][j] - '=');
		tmp = ms->exp;
		i++;
	}
}

static void	ft_export_add(char *str, t_ms *ms, int dif)
{
	ft_envlstadd_back(&ms->exp, ft_envlstnew(str));
	if (!dif)
		ft_envlstadd_back(&ms->envlst, ft_envlstnew(str));
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
			printf("es: %s\n", str);
			break ;
		}
		tmp = tmp->next;
	}
	return ;
}
