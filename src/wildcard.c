#include "minishell.h"
#include "libft.h"
#include "get_next_line.h"
#include "fractol_utils.h"
#include <dirent.h>

static char	*ft_check_dir(char **ls, struct dirent *dir, char *wild);
static char	*ft_check_file(char *file, char *wild);
static int	ft_last_cmp(char *file, char *wild);
static int	ft_first_cmp(char *file, char *wild);

char	**ft_wildcard(char **ls)
{
	struct dirent	*dir;
	DIR				*open_dir;
	char			*tmp;
	char			**wild;

	open_dir = opendir(".");
	if (!open_dir)
		return (NULL);
	dir = readdir(open_dir);
	tmp = NULL;
	while (dir)
	{
		tmp = ft_check_dir(ls, dir, tmp);
		dir = readdir(open_dir);
	}
	closedir(open_dir);
	if (!tmp)
		return (ls);
	wild = ft_split(tmp, '\n');
	free(tmp);
	return (wild);
}

static char	*ft_check_dir(char **ls, struct dirent *dir, char *wild)
{
	char	*file;
	char	*tmp;
	int		i;

	i = -1;
	while (ls[++i])
	{
		file = ft_check_file(dir->d_name, ls[i]);
		if (file)
		{
			if (!wild)
				wild = ft_strdup(file);
			else
			{
				tmp = wild;
				wild = ft_strjoin_va("%s\n%s", tmp, file);
				free(file);
				free(tmp);
			}
		}
	}
	return (wild);
}

static char	*ft_check_file(char *file, char *wild)
{
	size_t		i;

	i = 0;
	if (file[0] == '.')
		return (NULL);
	while (wild[i] && wild[i] != '*')
		i++;
	if (i == ft_strlen(wild))
		return (NULL);
	if (!i && !ft_last_cmp(file, wild))
		return (ft_strdup(file));
	else if (i && !ft_first_cmp(file, wild) && !ft_last_cmp(file, wild))
		return (ft_strdup(file));
	return (NULL);
}

static int	ft_first_cmp(char *file, char *wild)
{
	int	i;

	i = -1;
	while (wild[++i] && wild[i] != '*' && file[i])
	{
		if (wild[i] != file[i])
			return (wild[i] - file[i]);
	}
	if (wild[i] == '*')
		return (0);
	else
		return (1);
}

static int	ft_last_cmp(char *file, char *wild)
{
	int	f;
	int	w;

	f = ft_strlen(file);
	w = ft_strlen(wild);
	while ((--w >= 0 && --f >= 0) && wild[w] != '*')
	{
		if (wild[w] != file[f])
			return (wild[w] - file[f]);
	}
	if (wild[w] == '*')
		return (0);
	else
		return (1);
}
