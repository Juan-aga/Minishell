#include "lexer.h"
#include "minishell.h"
#include "libft.h"
#include "fractol_utils.h"
#include "ft_printf.h"

void	expand_tokens(t_lexer *lexer, t_ms *ms)
{
	t_token		*tk;
	int			i;

	tk = lexer->token_list;
	i = 0;
	while (tk)
	{
		if (tk->status != SINGLE_QUOTE && tk->type != DELIMITER && \
			ft_strchr(tk->str, '$'))
		{
			while (tk->str[i] && tk->str[i] != '\0')
			{
				i += replace_next_dollar(&tk->str[i], ms, tk);
				if (i < 0)
					i = 0;
			}
			i = 0;
		}
		tk = tk->next;
	}
}

int	replace_next_dollar(char *str, t_ms *ms, t_token *tok)
{
	char		*name;
	int			len;
	t_envlst	*env;

	name = get_var_name(str);
	if (!name)
		return (1);
	if (ft_strnstr(name, "$?", ft_strlen(name)))
		return (replace_exit_status(tok, ms, name));
	if (ft_isdigit(name[1]) || !ft_isalpha(name[1]))
		return (replace_next_char(tok, ms, name));
	env = ft_getenv(&name[1], ms->envlst);
	len = ft_strlen(name);
	if (!env)
	{
		tok->str = replace_env_var(tok->str, name, "");
		if (tok->status == NORMAL)
			token_free(tok);
		return (-len);
	}
	tok->str = replace_env_var(tok->str, name, env->value);
	return (len);
}

int	replace_exit_status(t_token *tok, t_ms *ms, char *free_str)
{
	char	*status;

	free(free_str);
	status = ft_itoa(ms->exit_status);
	tok->str = replace_env_var(tok->str, ft_strdup("$?"), status);
	free(status);
	return (1);
}

int	replace_next_char(t_token *tok, t_ms *ms, char *free_str)
{
	char		*str;
	t_envlst	*env;

	env = ft_getenv(&free_str[1], ms->envlst);
	if (env)
	{
		tok->str = replace_env_var(tok->str, free_str, env->value);
		return (1);
	}
	if (!ft_isdigit(free_str[1]))
	{
		free(free_str);
		return (1);
	}
	str = ft_substr(free_str, 0, 2);
	tok->str = replace_env_var(tok->str, str, "");
	free(free_str);
	return (-2);
}
