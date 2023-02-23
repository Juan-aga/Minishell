#include "lexer.h"
#include "minishell.h"
#include "libft.h"
#include "ft_printf.h"

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
	trim_quotes_token(lexer.token_list);
	remove_empty_tokens(lexer.token_list);
	token = lexer.token_list;
	lexer.n_tokens = 0;
	while (token != NULL)
	{
		ft_printf("str: %s\n", token->str);
		ft_printf("type: %d\n", token->type);
		ft_printf("status: %d\n", token->status);
		ft_printf("escaped: %d\n", token->escaped);
		ft_printf("next: %p\n", token->next);
		ft_printf("----------------------------\n");
		token = token->next;
	}
	lexer_free(&lexer);
}
