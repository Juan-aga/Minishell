#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>

/*		define colors letters		*/
# define CGREEN "\033[1;34;42m"
# define CRED "\033[1;37;41m"
# define CBLUE "\033[1;33;44m"
# define CWHITE "\033[30;47m"
# define CRESET "\x1B[0m"

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
	int				exit;
	int				exit_status;
	char			*prompt;
	char			**env;
	pid_t			pid;
}	t_ms;

/*	cmdlst functions				*/
/*	create a new cmd list				*/
t_cmdlst	*ft_cmdlstnew(void);
/*	add a new nodo at the end of tje list		*/
void		ft_cmdlstadd_back(t_cmdlst **cmdlst, t_cmdlst *add);
/*	return a pointer to the last nodo of the list	*/
t_cmdlst	*ft_cmdlstlast(t_cmdlst *cmdlst);
/*	free the list					*/
void		ft_free_cmdlst(t_cmdlst	*cmdlst);

/*		enviroment functions						*/
void		ft_get_env(t_ms *ms, char **env);

#endif
