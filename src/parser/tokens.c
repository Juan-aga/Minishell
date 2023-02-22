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

void	compund_tokens(t_token *tk)
{
	t_token	*tmp;

	while (tk)
	{
		if (tk->type == CHAR_GREAT && tk->next && tk->next->type == CHAR_GREAT)
		{
			tmp = tk->next;
			free(tk->str);
			tk->str = ft_strdup(">>");
			tk->type = CHAR_GREATGREAT;
			tk->next = tk->next->next;
			token_free(tmp);
		}
		else if (tk->type == CH_LESS && tk->next && tk->next->type == CH_LESS)
		{
			tmp = tk->next;
			free(tk->str);
			tk->str = ft_strdup("<<");
			tk->type = CHAR_LESSLESS;
			tk->next = tk->next->next;
			tk->next->type = CHAR_DELIMITER;
			token_free(tmp);
		}
		tk = tk->next;
	}
}

t_token	*escape_token(t_token *token, char *input, int *j, int *i)
{
	token->str[(*j)++] = input[(*i)];
	token->str[(*j)++] = input[++(*i)];
	token->escaped = ESCAPED;
	token = token_init(token, ft_strlen(input) - *i);
	*j = 0;
	return (token);
}
