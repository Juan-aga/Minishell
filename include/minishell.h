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
	struct s_cmdlst	*prev;
	char			*path;
	char			**arg;
	char			*fd_in_file;
	char			*fd_out_file;
	int				fd_in;
	int				fd_out;
}	t_cmdlst;

typedef struct s_envlst
{
	struct s_envlst	*next;
	struct s_envlst	*prev;
	char			*var;
	char			*value;
}	t_envlst;

typedef struct s_ms
{
	struct s_cmdlst	*cmdlst;
	struct s_envlst	*envlst;
	struct s_envlst	*exp;
	int				num_com;
	int				exe;
	int				exit;
	int				exit_status;
	int				*pipe;
	char			*prompt;
	char			**path;
	char			**env;
	pid_t			pid;
}	t_ms;

/*	cmdlst functions								*/
/*	create a new cmd list							*/
t_cmdlst	*ft_cmdlstnew(void);
/*	add a new nodo at the end of tje list			*/
void		ft_cmdlstadd_back(t_cmdlst **cmdlst, t_cmdlst *add);
/*	return a pointer to the last nodo of the list	*/
t_cmdlst	*ft_cmdlstlast(t_cmdlst *cmdlst);
/*	free the list									*/
void		ft_free_cmdlst(t_cmdlst	*cmdlst);

/*		envlst functions							*/
t_envlst	*ft_envlstnew(char *str);
void		ft_envlstadd_back(t_envlst **envlst, t_envlst *add);
t_envlst	*ft_envlstlast(t_envlst *envlst);
void		ft_free_envlst(t_envlst *envlst);
t_envlst	*ft_envlst_fill(t_envlst *envlst, char *str);
/*		envlst utils								*/
t_envlst	*ft_copy_env(char **env);
void		ft_envlst_short(t_envlst **lst);
void		ft_envlst_to_env(t_ms *ms);
void		ft_envlst_del(t_envlst **lst);

/*		exit builtin				*/
/*		it change exit to 0			*/
void		ft_exit(t_ms *ms);
void		ft_pwd(t_ms *ms);
void		ft_cd(char *str, t_ms *ms);
/*		enviroment builtin functions						*/
void		ft_export(char **str, t_ms *ms);
void		ft_env(t_ms *ms);
void		ft_unset(char **str, t_ms *ms);
void		ft_export_to_env(char *str, t_envlst *envlst);

/*
 * 		check if a variable is in the env.
 * 		with c=E is for export use, it return 0 if there is no '='
 * 		if it exist it returns the position in env[ ]
 * 		else it returns  0;						*/
int			ft_check_env(char *str, t_ms *ms, char c);
/*		builtin utils				*/
int			ft_is_builtin(t_ms *ms, t_cmdlst *tmp);
void		ft_accept_redirections(t_ms *ms, t_cmdlst *tmp);
/*		enviroment utils				*/
void		ft_free_array(char **str, int i);
/*
 * 		do a copy of the array with extra space
 * 		if add is 0 it only do a copy.		*/
char		**ft_copy_array(char **src, int add);
/*
		delete 'del' items from an array.
		if del is < 1 don't do anything.		*/
void		ft_del_items_array(char **str, int del);
/*
		duplicates functionality of getenv()
		but works with the env of minishell.
		it returns a ponter to the envlst if exist
		else return NULL			*/
t_envlst	*ft_getenv(char *str, t_envlst *lst);
void		ft_shlvl_update(t_ms *ms);
/*		redirections				*/
void		ft_exec(t_ms *ms);
/*		redirections utils			*/
void		ft_dup(int in, int out);
void		ft_close_pipe(t_ms *ms);
void		ft_get_path(t_ms *ms, t_cmdlst *tmp);
/*		pruebas, para borar			*/
void		ft_pruebas(char *str, t_ms *ms);

#endif
