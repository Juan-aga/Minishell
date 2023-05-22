#include "minishell.h"

/* Iterate over all the tokens and replace every * on them with the files that
ls returned */

void	expand_all_wildcards(t_lexer *lex)
{
	t_token	*token;
	char	**wildcards;

	token = lex->token_list;
	while (token)
	{
		if (token->str && token->type == CH_NORMAL && \
			token->status == NO_QUOTE && ft_strchr(token->str, '*'))
		{
			wildcards = ft_wildcard(&token->str);
			if (wildcards)
			{
				token = expand_wildcard(token, wildcards);
				ft_free_array(wildcards, 0);
			}
		}
		token = token->next;
	}
}

/* This function creates a token for every wildcard in the given wildcards array
so it can pass it as a parameter to the executable */

t_token	*expand_wildcard(t_token *tok, char **wildcards)
{
	int		i;
	t_token	*prev;
	t_token	*next;

	i = -1;
	prev = tok->prev;
	next = tok->next;
	free_token(tok);
	while (wildcards[++i])
	{
		tok = new_token(prev, 0);
		free(tok->str);
		tok->str = ft_strdup(wildcards[i]);
		prev->next = tok;
		prev = tok;
		tok->type = EXPANDED;
	}
	if (next)
		tok->next = next;
	return (tok);
}
