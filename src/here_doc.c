#include "minishell.h"
#include "libft.h"
#include <readline/readline.h>
#include <sys/wait.h>

int	ft_here_doc(char *limiter)
{
	int		fd[2];
	int		size;
	char	*line;

	pipe(fd);
	size = ft_strlen(limiter) + 1;
	while (42)
	{
		line = readline (HEREDOC_TEXT);
		if (!line)
			break ;
		if (!ft_strncmp(line, limiter, size))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd[1]);
		ft_putstr_fd("\n", fd[1]);
		free(line);
	}
	close(fd[1]);
	return (fd[0]);
}
