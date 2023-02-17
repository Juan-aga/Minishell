#include "../include/lexer.h"
#include "../include/minishell.h"
#include "../lib/libft-juan-aga/include/libft.h"
#include "../lib/libft-juan-aga/include/ft_printf.h"

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

void	lexer_init(char *input, t_token *token)
{
	int		i;
	int		j;
	int		type;

	i = -1;
	j = 0;
	while (input[++i] != '\0')
	{
		type = ft_get_token_type(input[i]);
		if (type == CHAR_ESCAPE)
		{
			token->str[j++] = input[++i];
			token->status = ESCAPED;
		}
		else if (type == CHAR_NORMAL)
			token->str[j++] = input[i];
		else if (type == CHAR_SPACE && j > 0)
		{
			token = token_init(token, ft_strlen(input) - i);
			j = 0;
		}
		else
			token = other_tokens(token, type, &j, ft_strlen(input) - i);
	}
	token->str[j] = '\0';
}

void	debug_tokenize(char *input)
{
	t_lexer	lexer;
	t_token	*token;

	if (input == NULL)
		return ;
	lexer.token_list = token_init(NULL, ft_strlen(input));
	lexer_init(input, lexer.token_list);
	if (close_quotes(lexer.token_list, CHAR_SQUOTE) || \
		close_quotes(lexer.token_list, CHAR_DQUOTE))
		return ;
	clean_tokens(lexer.token_list);
	token = lexer.token_list;
	lexer.n_tokens = 0;
	while (token != NULL)
	{
		ft_printf("str: %s\n", token->str);
		ft_printf("type: %d\n", token->type);
		ft_printf("status: %d\n", token->status);
		ft_printf("next: %p\n", token->next);
		ft_printf("----------------------------\n");
		token = token->next;
	}
	lexer_free(&lexer);
}
