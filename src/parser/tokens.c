#include "lexer.h"
#include "minishell.h"
#include "libft.h"
#include "ft_printf.h"

int	close_quotes(t_token *tok, char quote_char)
{
	int	flag;
	int	i;

	flag = 0;
	while (tok)
	{
		if (flag % 2 != 0)
			tok->status = quote_char;
		i = 0;
		while (tok->str[i] != '\0')
		{
			if (tok->str[i] == CHAR_ESCAPE && tok->str[i + 1] == quote_char)
				flag--;
			if (tok->str[i] == quote_char)
				flag++;
			i++;
		}
		tok = tok->next;
	}
	if (flag % 2 != 0)
	{
		ft_printf("minishell: syntax error: unmatched quotes\n");
		return (1);
	}
	return (0);
}

t_token	*other_tokens(t_token *tok, int type, int *j, int len)
{
	if (type == CHAR_SPACE && *j == 0 && tok->status == NO_QUOTE)
		return (tok);
	else if (type == CHAR_DQUOTE || type == CHAR_SQUOTE)
		return (quote_token(tok, type, j, len));
	else if (*j > 0 && tok->status == NO_QUOTE)
	{
		tok = token_init(tok, 2);
		*j = 0;
	}
	else if (*j > 0 && tok->status != NO_QUOTE)
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
	if (token->str[0] == CHAR_DQUOTE || token->str[0] == CHAR_SQUOTE)
		return (token);
	*j = 0;
	token = token_init(token, ft_strlen(input) - *i);
	return (token);
}

/* I have done a little hack in line 103 to determine the kind of double
token, because on the token types enum, both GREATGREAT(61) and LESSLESS(62) are
GREAT(59) + 2 or LESS(60) + 2.
Norminette makes you make things like this >:(
*/
t_token	*redirect_token(t_token *token, char *input, int *j, int *i)
{
	if (*j > 0 && token->status == NO_QUOTE)
	{
		token = token_init(token, ft_strlen(input) - *i);
		*j = 0;
	}
	if ((input[*i] == CHAR_GREAT && input[*i + 1] == CHAR_GREAT) || \
		(input[*i] == CH_LESS && input[*i + 1] == CH_LESS))
	{
		token->type = input[(*i)] + 2;
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
	if (*j > 0 && (tok->str[0] != CHAR_DQUOTE && tok->str[0] != CHAR_SQUOTE))
	{
		tok = token_init(tok, len);
		*j = 0;
	}
	tok->str[(*j)++] = type;
	if (*j > 1 && tok->str[0] == type)
	{
		tok->status = type;
		tok->str[*j] = '\0';
		*j = 0;
		tok = token_init(tok, len);
	}
	return (tok);
}
