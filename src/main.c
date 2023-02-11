#include "minishell.h"
#include <stdlib.h>


static void ft_leaks(void)
{
	system("leaks -q minishell");
}

int	main(void)
{
	atexit(ft_leaks);
	return (0);
}
