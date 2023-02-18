#include "lexer.h"
#include "minishell.h"
#include "libft.h"

void	lexer_init(char *input, t_token *token)
{
	int		i;
	int		j;
	int		type;

	i = -1;
	j = 0;
	while (input[++i] != '\0')
	{
		type = get_token_type(input[i]);
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

void	lexer_free(t_lexer *lexer)
{
	t_token	*token;
	t_token	*next;

	token = lexer->token_list;
	while (token != NULL)
	{
		next = token->next;
		token_free(token);
		token = next;
	}
}

