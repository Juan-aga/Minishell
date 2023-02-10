#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_cmdlst
{
	struct s_cmdlst	*next;
	char		*path;
	char		**arg;
}	t_cmdlst;

typedef struct s_ms 
{
	struct s_cmdlst	*command;
	int		num_com;
	int		fd_in;
	int		fd_out;
	t_pid		pid;
}	t_ms;


