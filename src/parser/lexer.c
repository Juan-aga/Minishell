/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 18:23:12 by franmart          #+#    #+#             */
/*   Updated: 2023/05/22 18:23:13 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* This funtion does all the job of parsing the readline input, tokenizing it */

t_lexer	*ft_tokenize_line(char *input, t_ms *ms)
{
	t_lexer	*lexer;

	if (input == NULL || ft_strlen(input) == 0)
		return (0);
	lexer = ft_calloc(1, sizeof(t_lexer));
	lexer->error = 0;
	lexer->token_list = new_token(NULL, ft_strlen(input));
	lexer_init(input, lexer->token_list);
	if (close_quotes(lexer->token_list))
		lexer->error = 1;
	remove_empty_tokens(lexer);
	if (lexer_files(lexer->token_list))
		lexer->error = 1;
	trim_quotes_token(lexer->token_list);
	expand_all_wildcards(lexer);
	lexer->token_list = expand_tokens(lexer, ms);
	remove_empty_tokens(lexer);
	join_dollars(lexer->token_list);
	join_tokens(lexer->token_list);
	replace_tilde(lexer->token_list, ms);
	count_tokens(lexer);
	return (lexer);
}

/* I have considered consecutive tokens as multiple tokens as it's easier to
parse, but in some cases you have to output them together, for example
$USER$HOME or >>. For me they are two separate tokens that I must output
together, so I previously noted if the token has to be joined with the following
or not */

void	join_tokens(t_token *tk)
{
	char	*tmp_str;

	while (tk)
	{
		while (tk->next && tk->join_next && \
			(tk->type == CH_NORMAL || tk->type == CH_TILDE) && \
			(tk->next->type == CH_NORMAL || tk->next->type == CH_TILDE))
		{
			tmp_str = ft_strjoin(tk->str, tk->next->str);
			free(tk->str);
			tk->join_next = tk->next->join_next;
			tk->str = tmp_str;
			free_token(tk->next);
		}
		tk = tk->next;
	}
}

void	join_dollars(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		if (token->str && token->str[0] == '$' && ft_strlen(token->str) == 1 \
			&& token->next && token->join_next)
		{
			tmp = token;
			token = token->next;
			free_token(tmp);
			if (!token)
				return ;
		}
		token = token->next;
	}
}
