/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:11:14 by juan-aga          #+#    #+#             */
/*   Updated: 2023/06/07 10:44:28 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_take_path(char *dir);
static char	*ft_branch(char *file);
static void	ft_nodir(char **dir, t_ms *ms);

void	ft_prompt(t_ms *ms)
{
	char	*dir;
	char	*git;

	dir = NULL;
	dir = getcwd(dir, 0);
	if (!dir)
		ft_nodir(&dir, ms);
	git = ft_take_path(dir);
	if (git)
		git = ft_branch(git);
	if (!git)
	{
		git = ft_calloc(sizeof(char), 2);
		git[0] = '/';
	}
	if (ms->exit_status)
		ms->prompt = ft_strjoin_va("%s minishell %s%s %s %s%s %s %s%s$>%s ",
				CBLUE, CRESET, CWHITE, ft_strrchr(dir, '/'), CRESET, CBLUE,
				ft_strrchr(git, '/') + 1, CRESET, CRED, CRESET);
	else
		ms->prompt = ft_strjoin_va("%s minishell %s%s %s %s%s %s %s%s$>%s ",
				CBLUE, CRESET, CWHITE, ft_strrchr(dir, '/'), CRESET, CBLUE,
				ft_strrchr(git, '/') + 1, CRESET, CGREEN, CRESET);
	free(git);
	free(dir);
}

static char	*ft_take_path(char *dir)
{
	int		i;
	int		count;
	char	*tmp;
	char	*tmp2;

	i = -1;
	count = 0;
	while (dir[++i])
	{
		if (dir[i] == '/')
			count++;
	}
	tmp = ft_strdup(".git/HEAD");
	while (count - 1)
	{
		if (!access(tmp, F_OK))
			return (tmp);
		tmp2 = tmp;
		tmp = ft_strjoin("../", tmp2);
		free(tmp2);
		count--;
	}
	free(tmp);
	return (NULL);
}

static char	*ft_branch(char *file)
{
	char	*branch;
	int		fd;
	int		control;

	branch = ft_calloc(sizeof(char), 101);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		branch = NULL;
	else
	{
		control = read(fd, branch, 100);
		if (control < 0)
			branch = NULL;
		else
		{
			control = ft_strlen(branch);
			branch[control - 1] = '\0';
		}
	}
	free(file);
	return (branch);
}

static void	ft_nodir(char **dir, t_ms *ms)
{
	*dir = ft_strdup(ft_getenv("OLDPWD", ms->envlst)->value);
	ft_cd(*dir, ms);
}
