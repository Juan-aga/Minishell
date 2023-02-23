#include "lexer.h"
#include "minishell.h"
#include "libft.h"
#include "ft_printf.h"

void	compund_tokens(t_token *tk)
{
	check_append(tk);
	check_heredoc(tk);
}

void	check_append(t_token *tk)
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
			if (tk->next->next)
				tk->next = tk->next->next;
			else
				tk->next = NULL;
			token_free(tmp);
		}
		tk = tk->next;
	}
}

void	check_heredoc(t_token *tk)
{
	t_token	*tmp;

	while (tk)
	{
		if (tk->type == CH_LESS && tk->next && tk->next->type == CH_LESS)
		{
			tmp = tk->next;
			free(tk->str);
			tk->str = ft_strdup("<<");
			tk->type = CHAR_LESSLESS;
			if (tk->next->next)
			{
				tk->next = tk->next->next;
				tk->next->type = CHAR_DELIMITER;
				ft_printf("Heredoc! Delimiter: %s\n", tmp->next->str);
			}
			else
				tk->next = NULL;
			token_free(tmp);
		}
		tk = tk->next;
	}
}
