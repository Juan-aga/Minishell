#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include "fractol_utils.h"
#include <unistd.h>
//char *readline (char *prompt); 

static t_ms	ft_init(void);
static void	ft_free(t_ms ms);
static void	ft_prompt(t_ms *ms);

static void	ft_leaks(void)
{
	system("leaks -q minishell");
}

int	main(void)
{
	t_ms	ms;
	char	*prompt;
	int		exit;

	atexit(ft_leaks);
	exit = 1;
	ms = ft_init();
	while (exit)
	{
		prompt = readline (ms.prompt);
		printf("a puesto: %s\n", prompt);
		if (!prompt || !*prompt)
			exit = 0;
		free(prompt);
		free(ms.prompt);
		ft_prompt(&ms);
	}
	ft_free(ms);
	return (0);
}

static t_ms	ft_init(void)
{
	t_ms	ms;

	ms.num_com = 0;
	ms.fd_in = 0;
	ms.fd_out = 0;
	ms.exit_status = 0;
	ft_prompt(&ms);
	return (ms);
}

static void	ft_prompt(t_ms *ms)
{
	char	*dir;

	dir = NULL;
	dir = getcwd(dir, 1000);
	if (ms->exit_status)
		ms->prompt = ft_strjoin_va("%s minishell %s%s %s %s%s$>%s ", CBLUE,
				CRESET, CWHITE, ft_strrchr(dir, '/') + 1, CRESET, CRED, CRESET);
	else
		ms->prompt = ft_strjoin_va("%s minishell %s%s %s %s%s$>%s ", CBLUE,
				CRESET, CWHITE, ft_strrchr(dir, '/') + 1,
				CRESET, CGREEN, CRESET);
	free(dir);
}

static void	ft_free(t_ms ms)
{
	free(ms.prompt);
}
