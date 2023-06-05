/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 18:23:17 by franmart          #+#    #+#             */
/*   Updated: 2023/05/22 18:23:18 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Remove start and end quotes from the token string after it has been 
classified in single quotes or double quotes */

void	trim_quotes_token(t_token *token)
{
	char	*tmp;

	while (token)
	{
		if ((token->status == CH_SQUOTE || token->status == CH_DQUOTE) && \
			token->type != DELIMITER)
		{
			tmp = ft_substr(token->str, 1, ft_strlen(token->str) - 2);
			free(token->str);
			token->str = tmp;
		}
		token = token->next;
	}
}

/* checks if the char is a quote and ensures if the open and close quotes are
the same kind */

t_token	*quote_token(t_token *tok, int type, int *j, int len)
{
	if (*j > 0 && (tok->str[0] != CH_DQUOTE && tok->str[0] != CH_SQUOTE))
	{
		tok = new_token(tok, len);
		*j = 0;
	}
	tok->str[(*j)++] = type;
	tok->status = DOUBT_QUOTE;
	if (*j > 1 && tok->str[0] == type)
	{
		tok->status = type;
		tok->str[*j] = '\0';
		*j = 0;
		tok = new_token(tok, len);
	}
	return (tok);
}

/* Checks if any token in the token list is quoted, and raises an error if a
quoted token is not correct */

int	close_quotes(t_token *tok)
{
	int		flag;
	int		len;
	char	open_quote;

	flag = 0;
	while (tok)
	{
		if (tok->str[0] == CH_SQUOTE || tok->str[0] == CH_DQUOTE)
		{
			open_quote = tok->str[0];
			len = ft_strlen(tok->str);
			if ((len > 0 && tok->str[len - 1] != open_quote) || len == 1 || \
				tok->status == DOUBT_QUOTE)
				flag = 1;
		}
		tok = tok->next;
	}
	if (flag)
	{
		ft_putstr_fd("minishell: syntax error: unmatched quotes\n", 2);
		return (1);
	}
	return (0);
}
