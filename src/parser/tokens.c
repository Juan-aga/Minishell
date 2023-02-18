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
			if (token->str[i] == quote_char)
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

t_token	*other_tokens(t_token *token, int type, int *j, int len)
{
	if (type == CHAR_SPACE && *j == 0)
		return (token);
	else if (type == CHAR_DQUOTE || type == CHAR_SQUOTE)
	{
		token->str[*j] = type;
		token->status = type;
		*j += 1;
		return (token);
	}
	else if (*j > 0)
	{
		token = token_init(token, 2);
		*j = 0;
	}
	token->str[0] = type;
	token->type = type;
	*j = 0;
	token = token_init(token, len);
	return (token);
}
