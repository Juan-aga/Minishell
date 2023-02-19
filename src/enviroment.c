#include "libft.h"
#include "minishell.h"
#include <stdio.h>

void	ft_unset(char *str, t_ms *ms)
{
	t_envlst	*tmp;
	int			i;

	if (!str)
		return ;
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
	{
		printf("minishell: unset: \'%s\': not a valid identifier\n", str);
		ms->exit_status = 1;
		return ;
	}
	tmp = ft_getenv(str, ms->exp);
	if (!tmp)
		return ;
	ft_envlst_delete(str, ms->exp);
	ft_envlst_delete(str, ms->envlst);
/*
	i = (ft_check_env(str, ms, 'u'));
	if (i <= 0)
		return ;
	i -= 1;
	while (ms->env[i + 1])
	{
		free(ms->env[i]);
		ms->env[i] = ft_strdup(ms->env[i + 1]);
		i++;
	}
	free(ms->env[i]);
	ms->env[i] = ms->env[i + 1];
	free(ms->env[i + 1]);
	return ;*/
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
	exit(0);
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
