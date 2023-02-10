#include "minishell.h"
#include "libft.h"

t_cmdlst	*ft_cmdlstnew(void)
{
	t_cmdlst	*cmdlst;

	cmdlst = (t_cmdlst *) ft_calloc(1, sizeof(t_cmdlst));
	if (!cmdlst)
		return (NULL);
	cmdlst->path = NULL;
	cmdlst->arg = NULL;
	cmdlst->next = NULL;
}

void	ft_cmdlstadd_back(t_cmdlst **cmdlst, t_cmdlsdt *add)
{
	t_cmdlst	*last;

	if (!cmdlst || !add)
		return ;
	if (!cmdlst)
	{
		*cmdlst = add;
		return ;
	}
	last = ft_cmdlstlast(*cmdlst);
	last->next = add;
}

t_cmdlst	*ft_cmdlstlast(t_cmdlst *cmdlst)
{
	t_cmdlst	*last;

	last = cmdlst;
	if (cmdlst)
	{
		while (last->next)
		last = last->next;
	}
	return (last);
}

void	ft_free_cmdlst(t_cmdlst	*cmdlst)
{
	t_cmdlst	*tmp;

	while (cmdlst)
	{
		tmp = cmdlst->next;
		free(cmdlst);
		cmdlst = tmp;
	}
}
