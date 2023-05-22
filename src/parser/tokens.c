#include "minishell.h"

/* Classifies all tokens that are not redirections or normal chars. It removes
consecutive espaces, quotes a token, and allocates a new token if the input is
a special char */

t_token	*other_tokens(t_token *tok, int type, int *j, int len)
{
	if (type == CH_SPACE && *j == 0 && tok->status == NO_QUOTE)
	{
		if (tok->prev && tok->prev->status != NO_QUOTE)
			tok->prev->join_next = 0;
		return (tok);
	}
	else if (type == CH_DQUOTE || type == CH_SQUOTE)
		return (quote_token(tok, type, j, len));
	else if (*j > 0 && tok->status == NO_QUOTE)
	{
		tok = new_token(tok, 2);
		*j = 0;
	}
	else if ((*j > 0 && tok->status != NO_QUOTE) || tok->type == CH_TILDE)
	{
		tok->str[(*j)++] = type;
		return (tok);
	}
	tok->str[0] = type;
	tok->type = type;
	*j = 0;
	tok = new_token(tok, len);
	return (tok);
}

/* I have done a little hack in line 53 to determine the kind of double
token, because on the token types enum, both GREATGREAT(65) and LESSLESS(63) are
GREAT(62) + 3 or LESS(60) + 3.
Norminette makes you make things like this >:(

It checks the kind of redirection, and if the redirection char is inside quotes,
it treats it as a normal char */

t_token	*redirect_token(t_token *token, char *input, int *j, int *i)
{
	if (*j > 0 && token->status == NO_QUOTE)
	{
		token = new_token(token, ft_strlen(input) - *i);
		*j = 0;
	}
	if ((input[*i] == CH_GREAT && input[*i + 1] == CH_GREAT) || \
		(input[*i] == CH_LESS && input[*i + 1] == CH_LESS))
	{
		token->type = input[(*i)] + 3;
		token->str[(*j)++] = input[(*i)++];
		token->str[(*j)++] = input[(*i)];
		token->str[*j] = '\0';
	}
	else
	{
		token->str[(*j)++] = input[(*i)];
		token->str[*j] = '\0';
		token->type = input[(*i)];
		*j = 0;
	}
	token = new_token(token, ft_strlen(input) - *i);
	return (token);
}
