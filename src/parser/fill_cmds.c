#include "lexer.h"
#include "minishell.h"
#include "libft.h"
#include "ft_printf.h"

void	ft_fill_commands(t_ms *ms, t_lexer *lex)
{
	t_cmdlst	*cmd;
	t_token		*tok;
	int			n_cmds;

	if (!lex || !lex->token_list)
		return ;
	tok = lex->token_list;
	ms->cmdlst = ft_cmdlstnew();
	cmd = ms->cmdlst;
	n_cmds = 1;
	while (tok)
	{
		if (tok && tok->type == CH_PIPE && tok->next)
		{
			ft_cmdlstadd_back(&ms->cmdlst, ft_cmdlstnew());
			cmd = cmd->next;
			n_cmds++;
			tok = tok->next;
		}
		tok = fill_cmd(cmd, tok);
	}
	ms->num_com = n_cmds;
}

t_token	*fill_cmd(t_cmdlst *cmd, t_token *tok)
{
	if (tok->type == INFILE)
		cmd->fd_in_file = tok->str;
	if (tok->type == DELIMITER)
		cmd->fd_in_file = tok->str;
	if (tok->type == OUTFILE)
		cmd->fd_out_file = tok->str;
	if (tok->type == OUTFILE_APPEND)
		cmd->fd_out_file = tok->str;
	if (tok->type == CH_NORMAL && !cmd->arg)
		get_all_args(cmd, tok);
	if (tok->next)
		return (tok->next);
	return (0);
}

void	get_all_args(t_cmdlst *cmd, t_token *tok)
{
	int	i;
	int	n_args;

	i = -1;
	n_args = count_args(tok);
	cmd->arg = ft_calloc(n_args + 1, sizeof(char *));
	while (tok && tok->type != CH_PIPE)
	{
		if (tok->type == CH_NORMAL)
			cmd->arg[++i] = tok->str;
		tok = tok->next;
	}
	cmd->arg[i + 1] = NULL;
}

int	count_args(t_token *tok)
{
	int	i;

	i = 0;
	while (tok && tok->type != CH_PIPE)
	{
		if (tok->type == CH_NORMAL)
			i++;
		tok = tok->next;
	}
	return (i);
}
