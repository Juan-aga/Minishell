#include "lexer.h"
#include "minishell.h"
#include "libft.h"
#include "ft_printf.h"

void	trim_quotes_token(t_token *token)
{
	char	*tmp;

	while (token)
	{
		if (token->status == CHAR_SQUOTE)
		{
			tmp = ft_strtrim(token->str, "\'");
			free(token->str);
			token->str = tmp;
		}
		else if (token->status == CHAR_DQUOTE)
		{
			tmp = ft_strtrim(token->str, "\"");
			free(token->str);
			token->str = tmp;
		}
		token = token->next;
	}
}

int	close_quotes(t_token *token, char quote_char)
{
	int	flag;
	int	i;

	flag = 0;
	while (token)
	{
		if (flag % 2 != 0)
			token->status = quote_char;
		i = 0;
		while (token->str[i] != '\0')
		{
			if (token->str[i] == CHAR_ESCAPE && token->str[i + 1] == quote_char)
				flag--;
			if (token->str[i] == quote_char && token->status == NO_QUOTE)
				flag++;
			i++;
		}
		token = token->next;
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
	else if (((type == CHAR_DQUOTE || type == CHAR_SQUOTE) && !tok->escaped))
	{
		tok->str[(*j)++] = type;
		tok->status = type;
		return (tok);
	}
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
	return (token);
}
