/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 18:23:21 by franmart          #+#    #+#             */
/*   Updated: 2023/05/22 18:23:22 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_token_type(char c)
{
	if (c == '|')
		return (CH_PIPE);
	if (c == '\'')
		return (CH_SQUOTE);
	if (c == '\"')
		return (CH_DQUOTE);
	if (c == ' ')
		return (CH_SPACE);
	if (c == '>')
		return (CH_GREAT);
	if (c == '<')
		return (CH_LESS);
	if (c == 0)
		return (CH_NULL);
	if (c == '~')
		return (CH_TILDE);
	return (CH_NORMAL);
}

/* Allocate a new token and insert it after the given "token" var. The "size"
variable equals the lenght of the new token string */

t_token	*new_token(t_token *token, int size)
{
	if (token == NULL)
	{
		token = ft_calloc(1, sizeof(t_token));
		token->prev = NULL;
	}
	else
	{
		token->next = ft_calloc(1, sizeof(t_token));
		token->next->prev = token;
		token = token->next;
	}
	token->str = ft_calloc(size + 1, sizeof(char));
	token->type = CH_NORMAL;
	token->status = NO_QUOTE;
	token->escaped = NORMAL;
	token->join_next = 1;
	token->next = NULL;
	return (token);
}

/* Free the token and update the double linked list */

void	free_token(t_token *token)
{
	if (token->prev && token->next)
	{
		token->prev->next = token->next;
		token->next->prev = token->prev;
	}
	else if (token->prev)
		token->prev->next = NULL;
	else if (token->next)
		token->next->prev = NULL;
	if (token->str)
		free(token->str);
	if (token)
		free(token);
}

/* Remove empty tokens that can result from transformations like replacing
$USER when USER is not found on the environment */

void	remove_empty_tokens(t_lexer *lexer)
{
	t_token	*tok;
	t_token	*prev;
	t_token	*tmp;

	tok = lexer->token_list;
	prev = NULL;
	while (tok)
	{
		if (tok->str && tok->str[0] == '\0' && tok->status == NO_QUOTE)
		{
			if (prev)
				prev->next = tok->next;
			else
				lexer->token_list = tok->next;
			tmp = tok->next;
			free_token(tok);
			tok = tmp;
		}
		else
		{
			prev = tok;
			tok = tok->next;
		}
	}
}
