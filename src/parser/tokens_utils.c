#include "lexer.h"
#include "minishell.h"
#include "libft.h"

int	get_token_type(char c)
{
	if (c == '|')
		return (CHAR_PIPE);
	if (c == '&')
		return (CHAR_AMPERSAND);
	if (c == '\'')
		return (CHAR_SQUOTE);
	if (c == '\"')
		return (CHAR_DQUOTE);
	if (c == ';')
		return (CHAR_SEMICOL);
	if (c == ' ')
		return (CHAR_SPACE);
	if (c == '\\')
		return (CHAR_ESCAPE);
	if (c == '\n')
		return (CHAR_NL);
	if (c == '\t')
		return (CHAR_TAB);
	if (c == '>')
		return (CHAR_GREAT);
	if (c == '<')
		return (CHAR_LESS);
	if (c == 0)
		return (CHAR_NULL);
	return (CHAR_NORMAL);
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
	token->type = CHAR_NORMAL;
	token->status = NORMAL;
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
