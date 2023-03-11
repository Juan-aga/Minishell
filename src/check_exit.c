#include "minishell.h"
#include "push_swap_utils.h"
#include <limits.h>

static int	ft_limitsll(t_ms *ms, char *str);

int	ft_check_exit(t_ms *ms, char *str)
{
	int	i;

	i = 0;
	if (ft_issign(str[i]))
		i++;
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] != '\0' || ft_issign(str[i - 1]))
		return (0);
	if (!ft_limitsll(ms, str))
		return (0);
	return (1);
}

static int	ft_limitsll(t_ms *ms, char *str)
{
	__int128	i;

	i = ft_ato_int128(str);
	if (i < LLONG_MIN || i > LLONG_MAX)
		return (0);
	ms->exit_status = i;
	return (1);
}
