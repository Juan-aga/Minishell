/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:29:36 by franmart          #+#    #+#             */
/*   Updated: 2023/06/07 10:47:07 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "parser.h"

/* libft headers */
# include "fractol_utils.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
# include "push_swap_utils.h"

# include <dirent.h>
# include <fcntl.h>
# include <limits.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>

/*		define colors letters		*/
# define CGREEN "\001\033[1;34;42m\002"
# define CRED "\001\033[1;37;41m\002"
# define CBLUE "\001\033[1;33;44m\002"
# define CWHITE "\001\033[30;47m\002"
# define CRESET "\001\x1B[0m\002"
# define HEREDOC_TEXT "minishell here_doc> "

typedef struct s_lexer	t_lexer;

typedef struct s_cmdlst
{
	struct s_cmdlst	*next;
	struct s_cmdlst	*prev;
	char			*path;
	char			**arg;
	char			*fd_in_file;
	char			*fd_out_file;
	int				append;
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
	unsigned char	exit_status;
	int				*pipe;
	char			*prompt;
	char			**path;
	char			**env;
	t_lexer			*lexer;
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
void		ft_free_cmdlst(t_ms	*ms);

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

/*		free all at exit			*/
void		ft_free(t_ms *ms);

/*		exit builtin				*/
/*		it change exit to 0			*/
void		ft_exit_ms(t_ms *ms, char **num);
int			ft_check_exit(t_ms *ms, char *str);
__int128	ft_ato_int128(char *str);
void		ft_pwd(t_ms *ms);
void		ft_cd(char *str, t_ms *ms);
void		ft_echo(char **str);
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
void		ft_free_fork(t_ms *ms);
/*		pruebas, para borar			*/
void		ft_pruebas(char *str, t_ms *ms);
void		ft_prueba_wildcard(char **str);
/*		HERE_DOC					*/
/*
 * 		use readline and ft_putstr_fd 
 * 		to keep in a fd until find limiter.
 * 		return the fd to use for the next command
 * 		*/
int			ft_here_doc(char *limiter);
/*		WILDCARD					*/
/*
		return a char** with the result of use ls */
char		**ft_wildcard(char **ls);
/*
		ERRORS MSG					*/
void		ft_error_exe(char **arg, char *msg, t_ms *ms);
void		ft_error_file(char *file, t_ms *ms);

void		ft_prompt(t_ms *ms);

/* signals */
void		ft_sigint(int sig);
void		ft_sigint_proc(int sig);
void		ft_signheredoc(int sig);
#endif
