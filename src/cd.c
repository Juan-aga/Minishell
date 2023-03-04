#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "fractol_utils.h"
#include "ft_printf.h"

static void	ft_cd_error(char *str, t_ms *ms, int err, char **to_free);
static void	ft_cd_update(t_ms *ms, char **dir);
static int	ft_check_home(char *str, char **tmp, t_ms *ms);

void	ft_cd(char *str, t_ms *ms)
{
	char	**tmp;
	int		i;

	tmp = ft_calloc(sizeof(char *), 3);
	tmp[0] = getcwd(tmp[0], 0);
	i = ft_check_home(str, tmp, ms);
	if (i > 0)
		return ;
	else if (i < 0)
	{
		tmp[1] = ft_strjoin_va("%s/%s", tmp[0], str);
		if (chdir(tmp[1]) && chdir(str))
		{
			ft_cd_error(str, ms, 1, tmp);
			return ;
		}
	}
	ms->exit_status = 0;
	ft_cd_update(ms, tmp);
}

static int	ft_check_home(char *str, char **tmp, t_ms *ms)
{
	t_envlst	*lst;

	if (!str)
	{
		lst = ft_getenv("HOME", ms->exp);
		if (!lst)
		{
			ft_cd_error(str, ms, 0, tmp);
			return (1);
		}
		chdir(lst->value);
		return (0);
	}
	return (-1);
}

static void	ft_cd_error(char *str, t_ms *ms, int err, char **to_free)
{
	char	*tmp;

	if (!err)
		ft_putstr_fd("minishell: cd: HOME: not set\n", 2);
	else
	{
		tmp = ft_strjoin_va(
				"minishell: cd: %s: No such file or directory\n", str);
		ft_putstr_fd(tmp, 2);
		free(tmp);
	}
	ms->exit_status = 1;
	ft_free_array(to_free, 0);
}

static void	ft_cd_update(t_ms *ms, char **dir)
{
	t_envlst	*old;
	t_envlst	*pwd;
	char		**to_export;

	to_export = ft_calloc(sizeof(char *), 4);
	old = ft_getenv("OLDPWD", ms->exp);
	pwd = ft_getenv("PWD", ms->exp);
	if (!old)
		to_export[0] = ft_strdup("");
	else if (pwd)
		to_export[0] = ft_strjoin_va("OLDPWD=%s", pwd->value);
	else
		to_export[0] = ft_strjoin_va("OLDPWD=%s", dir[0]);
	if (pwd)
	{
		to_export[3] = NULL;
		to_export[3] = getcwd(to_export[3], 0);
		to_export[1] = ft_strjoin_va("PWD=%s", to_export[3]);
		free(to_export[3]);
	}
	ft_export(to_export, ms);
	ft_free_array(to_export, 0);
	ft_free_array(dir, 0);
}
