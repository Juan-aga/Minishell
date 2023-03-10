#include "lexer.h"
#include "minishell.h"
#include "libft.h"
#include "fractol_utils.h"
#include "ft_printf.h"

void	expand_wildcards(t_lexer *lex)
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
			token = expand_wildcard(token, wildcards);
			ft_free_array(wildcards, 0);
		}
		token = token->next;
	}
}

t_token	*expand_wildcard(t_token *tok, char **wildcards)
{
	int		i;
	t_token	*prev;
	t_token	*next;

	i = -1;
	prev = tok->prev;
	next = tok->next;
	token_free(tok);
	while (wildcards[++i])
	{
		tok = token_init(prev, 0);
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
