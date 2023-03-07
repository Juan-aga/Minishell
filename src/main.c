#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "fractol_utils.h"
#include <unistd.h>
#include "lexer.h"
#include "ft_printf.h"

static t_ms	ft_init(char **env);
static void	ft_free(t_ms ms);
static void	ft_prompt(t_ms *ms);


static void	ft_leaks(void)
{
	system("leaks -q minishell");
}

void	print_cmds(t_ms *ms)
{
	int			i;
	t_cmdlst	*cmd;

	i = 0;
	if (!ms || !ms->cmdlst)
		return ;
	cmd = ms->cmdlst;
	//ft_printf("Hay %d comandos\n\n", ms->num_com);
	while (cmd && cmd->arg)
	{
		while (cmd->arg[i])
		{
			ft_printf("Arg %d: %s\n", i, cmd->arg[i]);
			i++;
		}
		if (cmd->fd_in_file ||cmd->fd_out_file)
			ft_printf("IN %s, OUT %s\n", cmd->fd_in_file, cmd->fd_out_file);
		i = 0;
		cmd = cmd->next;
	}
}

int	main(int ac, char **av, char **env)
{
	t_ms	ms;
	t_lexer	*lex;
	char	*prompt;
	int		stat;

	atexit(ft_leaks);
	(void) ac;
	(void) av;
	ms = ft_init(env);
	while (ms.exit)
	{
		prompt = readline (ms.prompt);
		lex = ft_tokenize_line(prompt, &ms);
		ft_fill_commands(&ms, lex);
		//print_cmds(&ms);
//		ft_pruebas(prompt, &ms);
		ft_exec(&ms);
		if (!(!prompt || !*prompt))
			add_history(prompt);
		free(prompt);
		free(ms.prompt);
		if (lex)
			lexer_free(lex);
		if (ms.cmdlst)
			ft_free_cmdlst(ms.cmdlst);
		ft_prompt(&ms);
	}
	stat = ms.exit_status;
	ft_free(ms);
	return (stat);
}

static t_ms	ft_init(char **env)
{
	t_ms	ms;

	ms.num_com = 0;
	ms.exit = 1;
	ms.exit_status = 0;
	ft_prompt(&ms);
	ms.env = ft_copy_array(env, 0);
	ms.envlst = ft_copy_env(env);
	ms.exp = ft_copy_env(env);
	ft_shlvl_update(&ms);
	return (ms);
}

static void	ft_prompt(t_ms *ms)
{
	char	*dir;

	dir = NULL;
	dir = getcwd(dir, 0);
	if (ms->exit_status)
		ms->prompt = ft_strjoin_va("minishell > ");
		//ms->prompt = ft_strjoin_va("%s minishell %s%s %s %s%s$>%s ", CBLUE,
				//CRESET, CWHITE, ft_strrchr(dir, '/') + 1, CRESET, CRED, CRESET);
	else
		ms->prompt = ft_strjoin_va("minishell > ");
		//ms->prompt = ft_strjoin_va("%s minishell %s%s %s %s%s$>%s ", CBLUE,
				//CRESET, CWHITE, ft_strrchr(dir, '/') + 1,
				//CRESET, CGREEN, CRESET);
	free(dir);
}

static void	ft_free(t_ms ms)
{
	free(ms.prompt);
	ft_free_array(ms.env, 0);
	ft_free_envlst(ms.envlst);
	ft_free_envlst(ms.exp);
}
