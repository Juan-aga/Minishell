#include "lexer.h"
#include "minishell.h"
#include "libft.h"
#include "ft_printf.h"

t_lexer	*debug_tokenize(char *input, t_ms *ms)
{
	t_lexer	*lexer;
	t_token	*token;

	if (input == NULL)
		return (0);
	lexer = ft_calloc(1, sizeof(t_lexer));
	lexer->token_list = token_init(NULL, ft_strlen(input));
	lexer_init(input, lexer->token_list);
	if (close_quotes(lexer->token_list))
		return (0);
	trim_quotes_token(lexer->token_list);
	remove_empty_tokens(lexer->token_list);
	if (lexer_files(lexer->token_list))
		return (0);
	token = lexer->token_list;
	lexer->n_tokens = 0;
	while (token)
	{
		ft_printf("str: %s\n", token->str);
		ft_printf("type: %d\n", token->type);
		ft_printf("status: %d\n", token->status);
		ft_printf("escaped: %d\n", token->escaped);
		ft_printf("next: %p\n", token->next);
		get_variable_value(token->str, ms->envlst);
		ft_printf("----------------------------\n");
		lexer->n_tokens++;
		token = token->next;
	}
	lexer_free(lexer);
	return (lexer);
}
