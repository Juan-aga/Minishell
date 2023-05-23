/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 18:23:07 by franmart          #+#    #+#             */
/*   Updated: 2023/05/22 18:23:08 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* this function is pretty stacked. It reads every char in input and calls other
functions to classify each type of token, creating new empty tokens when
necessary */

void	lexer_init(char *input, t_token *token)
{
	int		i;
	int		j;
	int		type;

	i = -1;
	j = 0;
	while (input[++i] != '\0')
	{
		type = get_token_type(input[i]);
		if ((type == CH_GREAT || type == CH_LESS) && \
			token->status == NO_QUOTE)
			token = redirect_token(token, input, &j, &i);
		else if (type == CH_NORMAL)
			token->str[j++] = input[i];
		else if (type == CH_SPACE && j > 0 && token->status == NO_QUOTE)
		{
			token->join_next = 0;
			token = new_token(token, ft_strlen(input) - i);
			j = 0;
		}
		else
			token = other_tokens(token, type, &j, ft_strlen(input) - i);
	}
}

void	lexer_free(t_lexer *lexer)
{
	t_token	*token;
	t_token	*next;

	if (!lexer)
		return ;
	token = lexer->token_list;
	while (token != NULL)
	{
		next = token->next;
		free_token(token);
		token = next;
	}
	free(lexer);
}

/* It travels the token list and assigns the corresponding file token type
depending on the token delimiter it found for it */

int	lexer_files(t_token *token)
{
	t_token	*tok;

	tok = token;
	while (tok)
	{
		if (tok->type > 59 && tok->type < 66 && \
			(!tok->next || tok->next->type != -1))
		{
			ft_putstr_fd("No filename given\n", 2);
			return (1);
		}
		if (tok->type == CH_LESS)
			tok->next->type = INFILE;
		if (tok->type == CH_GREAT)
			tok->next->type = OUTFILE;
		if (tok->type == CH_LESSLESS)
			tok->next->type = DELIMITER;
		if (tok->type == CH_GREATGREAT)
			tok->next->type = OUTFILE_APPEND;
		tok = tok->next;
	}
	return (0);
}

int	count_tokens(t_lexer *lexer)
{
	t_token	*tok;
	int		i;

	tok = lexer->token_list;
	i = 0;
	while (tok)
	{
		i++;
		tok = tok->next;
	}
	lexer->n_tokens = i;
	return (i);
}
