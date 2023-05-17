#include "lexer.h"
#include "minishell.h"
#include "libft.h"
#include "ft_printf.h"

t_lexer	*ft_tokenize_line(char *input, t_ms *ms)
{
	t_lexer	*lexer;

	if (input == NULL || ft_strlen(input) == 0)
		return (0);
	lexer = ft_calloc(1, sizeof(t_lexer));
	lexer->error = 0;
	lexer->token_list = token_init(NULL, ft_strlen(input));
	lexer_init(input, lexer->token_list);
	if (close_quotes(lexer->token_list))
		lexer->error = 1;
	remove_empty_tokens(lexer);
	if (lexer_files(lexer->token_list))
		lexer->error = 1;
	trim_quotes_token(lexer->token_list);
	expand_wildcards(lexer);
	expand_tokens(lexer, ms);
	join_dollars(lexer->token_list);
	join_tokens(lexer->token_list);
	replace_tilde(lexer->token_list, ms);
	count_tokens(lexer);
	return (lexer);
}

void	join_tokens(t_token *tk)
{
	char	*tmp_str;

	while (tk)
	{
		while (tk->next && tk->join_next && \
			(tk->type == CH_NORMAL || tk->type == CH_TILDE) && \
			(tk->next->type == CH_NORMAL || tk->next->type == CH_TILDE))
		{
			tmp_str = ft_strjoin(tk->str, tk->next->str);
			free(tk->str);
			tk->join_next = tk->next->join_next;
			tk->str = tmp_str;
			token_free(tk->next);
		}
		tk = tk->next;
	}
}

void	join_dollars(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		if (token->str[0] == '$' && ft_strlen(token->str) == 1 && \
			token->next && token->join_next)
		{
			tmp = token;
			token = token->next;
			token_free(tmp);
			if (!token)
				return ;
		}
		token = token->next;
	}
}
// add these lines to ft_tokenize_line while debugging
/*
	t_token	*token = lexer->token_list;
	while (token)
	{
		ft_printf("str: %s\n", token->str);
		ft_printf("type: %d\n", token->type);
		ft_printf("status: %d\n", token->status);
		ft_printf("escaped: %d\n", token->escaped);
		ft_printf("join_next: %d\n", token->join_next);
		ft_printf("next: %p\n", token->next);
		ft_printf("----------------------------\n");
		lexer->n_tokens++;
		token = token->next;
	}
	lexer_free(lexer);
*/
