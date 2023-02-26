#include "lexer.h"
#include "minishell.h"
#include "libft.h"
#include "ft_printf.h"

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
		if (type == CH_ESCAPE)
			token = escape_token(token, input, &j, &i);
		else if ((type == CH_GREAT || type == CH_LESS) && \
			token->status == NO_QUOTE)
			token = redirect_token(token, input, &j, &i);
		else if (type == CH_NORMAL)
			token->str[j++] = input[i];
		else if (type == CH_SPACE && j > 0 && token->status == NO_QUOTE)
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

int	lexer_files(t_token *token)
{
	t_token	*tok;

	tok = token;
	while (tok)
	{
		if (tok->type > 59 && tok->type < 66 && \
			(!tok->next || tok->next->type != -1))
		{
			ft_printf("No filename given\n");
			return (1);
		}
		if (tok->type == CH_LESS)
			tok->next->type = INFILE;
		if (tok->type == CH_GREAT)
			tok->next->type = OUTFILE;
		if (tok->type == CH_LESSLESS)
			tok->next->type = DELIMITER;
		if (tok->type == CH_GREATGREAT)
			tok->next->type = OUTFILE_APPEND;
		tok = tok->next;
	}
	return (0);
}
