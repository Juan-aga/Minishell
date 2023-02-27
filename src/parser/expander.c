#include "lexer.h"
#include "minishell.h"
#include "libft.h"
#include "fractol_utils.h"
#include "ft_printf.h"

void	expand_tokens(t_lexer *lexer)
{
	t_token	*tok;

	tok = lexer->token_list;
	while (tok)
	{
		tok = tok->next;
	}
}

t_envlst	*get_variable_value(char *str, t_envlst *env)
{
	int			i;
	char		*word;
	char		*v_name;
	t_envlst	*env_variable;

	word = ft_strchr(str, '$');
	env_variable = 0;
	if (word)
	{
		i = 1;
		while ((word[i] != '\0' && ft_isalpha(word[i])) || word[i] == '_')
			i++;
		v_name = ft_substr(word, 1, i - 1);
		env_variable = ft_getenv(v_name, env);
		free(v_name);
		if (!env_variable)
			return (0);
	}
	return (env_variable);
}
