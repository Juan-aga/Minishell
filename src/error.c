#include "minishell.h"
#include "libft.h"

void	ft_error_exe(char **arg, char *msg)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(arg[0], 2);
	ft_putstr_fd(msg, 2);
	ft_free_array(arg, 0);
	exit(-1);
}

void	ft_error_file(char **arg, char *file, char *msg)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(msg, 2);
	ft_free_array(arg, 0);
	exit(-1);
}
