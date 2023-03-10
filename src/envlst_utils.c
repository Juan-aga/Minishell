#include "minishell.h"
#include "libft.h"
#include "fractol_utils.h"

t_envlst	*ft_copy_env(char **env)
{
	t_envlst	*new;
	int			i;

	i = 0;
	new = NULL;
	if (!*env)
		return (NULL);
	while (env[i])
	{
		if (i == 0)
			new = ft_envlstnew(env[i]);
		else
			ft_envlstadd_back(&new, ft_envlstnew(env[i]));
		i++;
	}
	return (new);
}

void	ft_envlst_short(t_envlst **lst)
{
	int			diff;
	char		*change;
	t_envlst	*tmp;

	tmp = *lst;
	if (!*lst)
		return ;
	while (tmp->next)
	{
		diff = ft_strncmp(tmp->var, tmp->next->var, 100);
		if (diff > 0)
		{
			change = tmp->var;
			tmp->var = tmp->next->var;
			tmp->next->var = change;
			change = tmp->value;
			tmp->value = tmp->next->value;
			tmp->next->value = change;
			tmp = *lst;
		}
		else
			tmp = tmp->next;
	}
}

void	ft_envlst_to_env(t_ms *ms)
{
	t_envlst	*tmp;
	int			i;
	char		**new;

	i = 0;
	tmp = ms->envlst;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	tmp = ms->envlst;
	new = ft_calloc(sizeof(char *), i + 1);
	if (!new)
		return ;
	i = 0;
	while (tmp)
	{
		new[i] = ft_strjoin_va("%s=%s", tmp->var, tmp->value);
		i++;
		tmp = tmp->next;
	}
	ms->env = new;
}

void	ft_envlst_del(t_envlst **lst)
{
	if (!*lst)
		return ;
	if ((*lst)->next && (*lst)->prev)
	{
		(*lst)->prev->next = (*lst)->next;
		(*lst)->next->prev = (*lst)->prev;
	}
	else if ((*lst)->next)
		(*lst)->next->prev = NULL;
	else if ((*lst)->prev)
		(*lst)->prev->next = NULL;
	(*lst)->prev = NULL;
	(*lst)->next = NULL;
	ft_free_envlst(*lst);
}
