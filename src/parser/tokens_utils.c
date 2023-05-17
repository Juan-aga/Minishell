#include "lexer.h"
#include "minishell.h"
#include "libft.h"
#include "ft_printf.h"

int	get_token_type(char c)
{
	if (c == '|')
		return (CH_PIPE);
	if (c == '&')
		return (CH_AMPERSAND);
	if (c == '\'')
		return (CH_SQUOTE);
	if (c == '\"')
		return (CH_DQUOTE);
	if (c == ';')
		return (CH_SEMICOL);
	if (c == ' ')
		return (CH_SPACE);
	if (c == '\\')
		return (CH_ESCAPE);
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

t_token	*token_init(t_token *token, int size)
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

void	token_free(t_token *token)
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

void	remove_empty_tokens(t_lexer *lexer)
{
	t_token	*tok;
	t_token	*prev;
	t_token	*tmp;

	tok = lexer->token_list;
	prev = NULL;
	while (tok)
	{
		if (tok->str && tok->str[0] == '\0')
		{
			if (prev)
				prev->next = tok->next;
			else
				lexer->token_list = tok->next;
			tmp = tok->next;
			token_free(tok);
			tok = tmp;
		}
		else
		{
			prev = tok;
			tok = tok->next;
		}
	}
}

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
