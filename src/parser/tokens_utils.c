#include "lexer.h"
#include "minishell.h"
#include "libft.h"

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
	return (CH_NORMAL);
}

t_token	*token_init(t_token *token, int size)
{
	if (token == NULL)
		token = ft_calloc(1, sizeof(t_token));
	else
	{
		token->next = ft_calloc(1, sizeof(t_token));
		token = token->next;
	}
	token->str = ft_calloc(size, sizeof(char));
	token->type = CH_NORMAL;
	token->status = NO_QUOTE;
	token->escaped = NORMAL;
	token->next = NULL;
	return (token);
}

void	token_free(t_token *token)
{
	if (token->str)
		free(token->str);
	free(token);
}

void	remove_empty_tokens(t_token	*token)
{
	t_token	*next;
	t_token	*prev;

	while (token != NULL && token->next != NULL)
	{
		prev = token;
		token = token->next;
		next = token->next;
		if (token->str[0] == '\0')
		{
			token_free(token);
			prev->next = next;
		}
	}
}

void	trim_quotes_token(t_token *token)
{
	char	*tmp;

	while (token)
	{
		if (token->status == CH_SQUOTE || token->status == CH_DQUOTE)
		{
			tmp = ft_substr(token->str, 1, ft_strlen(token->str) - 2);
			free(token->str);
			token->str = tmp;
		}
		token = token->next;
	}
}
