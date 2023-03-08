#include "lexer.h"
#include "minishell.h"
#include "libft.h"
#include "ft_printf.h"

t_lexer	*ft_tokenize_line(char *input, t_ms *ms)
{
	t_lexer	*lexer;

	if (input == NULL)
		return (0);
	lexer = calloc(1, sizeof(t_lexer));
	lexer->token_list = token_init(NULL, ft_strlen(input));
	lexer_init(input, lexer->token_list);
	if (close_quotes(lexer->token_list))
	{
		lexer_free(lexer);
		return (0);
	}
	trim_quotes_token(lexer->token_list);
	remove_empty_tokens(lexer);
	if (lexer_files(lexer->token_list))
	{
		lexer_free(lexer);
		return (0);
	}
	expand_tokens(lexer, ms);
	count_tokens(lexer);
	return (lexer);
}

// add these lines to ft_tokenize_line while debugging
/*
	while (token)
	{
		ft_printf("str: %s\n", token->str);
		ft_printf("type: %d\n", token->type);
		ft_printf("status: %d\n", token->status);
		ft_printf("escaped: %d\n", token->escaped);
		ft_printf("next: %p\n", token->next);
		ft_printf("----------------------------\n");
		lexer->n_tokens++;
		token = token->next;
	}
	lexer_free(lexer);
*/
