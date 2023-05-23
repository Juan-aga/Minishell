/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 18:22:59 by franmart          #+#    #+#             */
/*   Updated: 2023/05/22 18:32:08 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Transforms tokens into a command list */

void	tokens_to_commands(t_ms *ms, t_lexer *lex)
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
		tok = fill_cmd(cmd, tok, ms);
		open_files_cmd(cmd);
	}
	ms->lexer = lex;
	ms->num_com = n_cmds;
}

/* This function fills the redirection part of the command and also the args */

t_token	*fill_cmd(t_cmdlst *cmd, t_token *tok, t_ms *ms)
{
	ms->print_prompt = 0;
	if (tok->type == INFILE)
		cmd->fd_in_file = tok->str;
	if (tok->type == DELIMITER)
	{
		cmd->fd_in_file = tok->str;
		cmd->append = 1;
		cmd->fd_in = ft_here_doc(tok->str);
	}
	if (tok->type == OUTFILE)
		cmd->fd_out_file = tok->str;
	if (tok->type == OUTFILE_APPEND)
	{
		cmd->fd_out_file = tok->str;
		cmd->append = 1;
	}
	ms->print_prompt = 1;
	if ((tok->type == CH_NORMAL || tok->type == EXPANDED) && !cmd->arg)
		get_all_args(cmd, tok);
	if (tok->next)
		return (tok->next);
	return (0);
}

/* Find all tokens until the end or until a pipe is encountered and save them
as arguments for the command in a 2D char array */

void	get_all_args(t_cmdlst *cmd, t_token *tok)
{
	int	i;
	int	n_args;

	i = -1;
	n_args = count_args(tok);
	cmd->arg = ft_calloc(n_args + 1, sizeof(char *));
	while (tok && tok->type != CH_PIPE)
	{
		if (tok->type == CH_NORMAL || tok->type == EXPANDED)
			cmd->arg[++i] = ft_strdup(tok->str);
		tok = tok->next;
	}
	cmd->arg[i + 1] = NULL;
}

/* Count the args previously so the get_all_args function can allocate the
number of rows for the 2D array */

int	count_args(t_token *tok)
{
	int	i;

	i = 0;
	while (tok && tok->type != CH_PIPE)
	{
		if (tok->type == CH_NORMAL || tok->type == EXPANDED)
			i++;
		tok = tok->next;
	}
	return (i);
}

/* Self explanatory, also raises errors if it encounters any */

int	open_files_cmd(t_cmdlst *cmd)
{
	if (cmd->fd_in_file && !cmd->append)
		cmd->fd_in = open(cmd->fd_in_file, O_RDONLY);
	if (cmd->fd_out_file && cmd->append)
		cmd->fd_out = open(cmd->fd_out_file, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (cmd->fd_out_file && !cmd->append)
		cmd->fd_out = open(cmd->fd_out_file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (cmd->fd_in == -1 || cmd->fd_out == -1)
		return (-1);
	return (0);
}
