#include "lexer.h"
#include "minishell.h"
#include "libft.h"
#include "ft_printf.h"

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
		tok = token_init(tok, 2);
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
	tok = token_init(tok, len);
	return (tok);
}

t_token	*escape_token(t_token *token, char *input, int *j, int *i)
{
	token->str[(*j)++] = input[(*i)];
	token->str[(*j)++] = input[++(*i)];
	token->escaped = ESCAPED;
	if (token->str[0] == CH_DQUOTE || token->str[0] == CH_SQUOTE)
		return (token);
	*j = 0;
	token = token_init(token, ft_strlen(input) - *i);
	return (token);
}

/* I have done a little hack in line 103 to determine the kind of double
token, because on the token types enum, both GREATGREAT(65) and LESSLESS(63) are
GREAT(62) + 3 or LESS(60) + 3.
Norminette makes you make things like this >:(
*/
t_token	*redirect_token(t_token *token, char *input, int *j, int *i)
{
	if (*j > 0 && token->status == NO_QUOTE)
	{
		token = token_init(token, ft_strlen(input) - *i);
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
	token = token_init(token, ft_strlen(input) - *i);
	return (token);
}

t_token	*quote_token(t_token *tok, int type, int *j, int len)
{
	if (*j > 0 && (tok->str[0] != CH_DQUOTE && tok->str[0] != CH_SQUOTE))
	{
		tok = token_init(tok, len);
		*j = 0;
	}
	tok->str[(*j)++] = type;
	tok->status = DOUBT_QUOTE;
	if (*j > 1 && tok->str[0] == type)
	{
		tok->status = type;
		tok->str[*j] = '\0';
		*j = 0;
		tok = token_init(tok, len);
	}
	return (tok);
}
