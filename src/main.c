/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:11:28 by juan-aga          #+#    #+#             */
/*   Updated: 2023/06/07 10:31:12 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_ms	*ft_init(char **env);
static void	ft_clean(t_ms *g_ms, char *prompt, t_lexer *lex);

t_ms		*g_ms;

int	main(int ac, char **av, char **env)
{
	t_lexer	*lex;
	char	*prompt;

	(void) ac;
	(void) av;
	g_ms = ft_init(env);
	rl_catch_signals = 0;
	while (g_ms->exit)
	{
		signal(SIGINT, ft_sigint);
		signal(SIGQUIT, ft_sigint);
		prompt = readline (g_ms->prompt);
		if (!prompt)
			ft_exit_ms(g_ms, NULL);
		lex = ft_tokenize_line(prompt, g_ms);
		tokens_to_commands(g_ms, lex);
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
