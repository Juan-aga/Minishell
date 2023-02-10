#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_cmdlst
{
	struct s_cmdlst	*next;
	char			*path;
	char			**arg;
}	t_cmdlst;

typedef struct s_ms
{
	struct s_cmdlst	*command;
	int				num_com;
	int				fd_in;
	int				fd_out;
	t_pid			pid;
}	t_ms;

/*	cmdlst functions				*/
/*	create a new cmd list				*/
t_cmdlst	*ft_cmdlstnew(void);
/*	add a new nodo at the end of tje list		*/
void		ft_cmdlstadd_back(t_cmdlst **cmdlst, t_cmdlsdt *add);
/*	return a pointer to the last nodo of the list	*/
t_cmdlst	*ft_cmdlstlast(t_cmdlst *cmdlst);
/*	free the list					*/
void		ft_free_cmdlst(t_cmdlst	*cmdlst);
