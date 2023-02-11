#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include "fractol_utils.h"
#include <unistd.h>
//char *readline (char *prompt); 

static t_ms	ft_init(void);
static void	ft_free(t_ms ms);

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
	}
	ft_free(ms);
	return (0);
}

static t_ms	ft_init(void)
{
	char	*user;
	t_ms	ms;

	ms.num_com = 0;
	ms.fd_in = 0;
	ms.fd_out = 0;
	user = getenv("USER");
	if (!user)
		user = "guest";
	ms.prompt = ft_strjoin_va("%s $ ", user);
	return (ms);
}

static void	ft_free(t_ms ms)
{
	free(ms.prompt);
}
