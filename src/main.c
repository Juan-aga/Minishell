#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include "fractol_utils.h"
#include <unistd.h>
#include "lexer.h"
#include "ft_printf.h"

static t_ms	*ft_init(char **env);
static void	ft_clean(t_ms *g_ms, char *prompt, t_lexer *lex);

t_ms		*g_ms;

/* static void	ft_leaks(void)
{
	system("leaks -q minishell");
} */

void	print_cmds(t_ms *ms)
{
	int			i;
	t_cmdlst	*cmd;

	i = 0;
	if (!ms || !ms->cmdlst)
		return ;
	cmd = ms->cmdlst;
	ft_printf("Hay %d comandos\n\n", ms->num_com);
	while (cmd && cmd->arg)
	{
		while (cmd->arg[i])
		{
			ft_printf("Arg %d: %s\n", i, cmd->arg[i]);
			i++;
		}
		if (cmd->fd_in_file || cmd->fd_out_file)
			ft_printf("IN %s, OUT %s\n", cmd->fd_in_file, cmd->fd_out_file);
		i = 0;
		cmd = cmd->next;
	}
}

int	main(int ac, char **av, char **env)
{
	t_lexer	*lex;
	char	*prompt;

	(void) ac;
	(void) av;
	g_ms = ft_init(env);
	while (g_ms->exit)
	{
		signal(SIGINT, ft_sigint);
		signal(SIGQUIT, ft_sigint);
		prompt = readline (g_ms->prompt);
		if (!prompt)
			ft_exit_ms(g_ms, NULL);
		lex = ft_tokenize_line(prompt, g_ms);
		ft_fill_commands(g_ms, lex);
		if (lex && !lex->error)
			ft_exec(g_ms);
		if (!(!prompt || !*prompt))
			add_history(prompt);
		ft_clean(g_ms, prompt, lex);
		ft_prompt(g_ms);
	}
	ft_free(g_ms);
	return (g_ms->exit_status);
}

static t_ms	*ft_init(char **env)
{
	t_ms	*ms;

	ms = ft_calloc(1, sizeof(t_ms));
	ms->num_com = 0;
	ms->exit = 1;
	ms->print_prompt = 1;
	ms->exit_status = 0;
	ft_prompt(ms);
	ms->env = ft_copy_array(env, 0);
	ms->envlst = ft_copy_env(env);
	ms->cmdlst = 0;
	ms->exp = ft_copy_env(env);
	ft_shlvl_update(ms);
	return (ms);
}

static void	ft_clean(t_ms *g_ms, char *prompt, t_lexer *lex)
{
	free(prompt);
	free(g_ms->prompt);
	lexer_free(lex);
	if (g_ms->cmdlst)
		ft_free_cmdlst(g_ms);
}

void	ft_free(t_ms *ms)
{
	free(ms->prompt);
	ft_free_array(ms->env, 0);
	ft_free_envlst(ms->envlst);
	ft_free_envlst(ms->exp);
	free(ms);
}
