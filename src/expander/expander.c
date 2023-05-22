#include "lexer.h"
#include "minishell.h"

/* This function travels all the token list and replaces every $ variable it
finds, but only when the token is not in single quotes or is a here_doc
delimiter. To travel a token string, it uses [i] that advances as many positions
as the variable value that it replaced. This function has to return a token
pointer because it can update the list head reference and it can cause leaks or
double frees */

t_token	*expand_tokens(t_lexer *lexer, t_ms *ms)
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
	return (lexer->token_list);
}

/* Replaces all dollar variables in an individual token. As it updates the
token string lenght, it has to return how many positions has moved. It's
negative if it couldn't find an env value for the given variable name, and it
moves back <strlen(var_name)> positions */

int	replace_next_dollar(char *str, t_ms *ms, t_token *tok)
{
	char		*name;
	int			len;
	t_envlst	*env;

	name = get_dollar_name(str);
	if (!name)
		return (1);
	if (ft_strnstr(name, "$?", ft_strlen(name)))
		return (replace_exit_status(tok, ms, name));
	if (ft_isdigit(name[1]) || !ft_isalpha(name[1]))
		return (replace_dollar_digit(tok, ms, name));
	env = ft_getenv(&name[1], ms->envlst);
	len = ft_strlen(name);
	if (!env)
	{
		tok->str = replace_str(tok->str, name, "");
		if (tok->status == 3 && tok->str[0] == '\0')
			free_token(tok);
		return (-len);
	}
	tok->str = replace_str(tok->str, name, env->value);
	return (len);
}

/* I handle the $? variable as a regular dollar, replacing $? for the
ms->exit_status */

int	replace_exit_status(t_token *tok, t_ms *ms, char *free_str)
{
	char	*status;

	free(free_str);
	status = ft_itoa(ms->exit_status);
	tok->str = replace_str(tok->str, ft_strdup("$?"), status);
	free(status);
	return (1);
}

/* This function is required to replicate a bash corner case in which we have
a variable name that starts with a number, for example $123abc. In this case,
bash prints 23abc, ommiting the 1 */

int	replace_dollar_digit(t_token *tok, t_ms *ms, char *free_str)
{
	char		*str;
	t_envlst	*env;

	env = ft_getenv(&free_str[1], ms->envlst);
	if (env)
	{
		tok->str = replace_str(tok->str, free_str, env->value);
		return (1);
	}
	if (!ft_isdigit(free_str[1]))
	{
		free(free_str);
		return (1);
	}
	str = ft_substr(free_str, 0, 2);
	tok->str = replace_str(tok->str, str, "");
	free(free_str);
	return (-2);
}

/* This function replaces a token that contains the tilde char with the HOME of
the user. It also adds a fallback in case that HOME is not found in the
environment, concatenating /Users/ with the USER name */

void	replace_tilde(t_token *tok, t_ms *ms)
{
	t_envlst	*home;
	t_token		*tk;
	char		*s;

	tk = tok;
	while (tk)
	{
		if (tk->str && tk->str[0] == '~' && (tk->str[1] == '/' || \
			tk->str[1] == '\0') && tk->type == CH_TILDE)
		{
			home = ft_getenv("HOME", ms->envlst);
			tk->type = EXPANDED;
			if (!home)
			{
				s = ft_strjoin("/Users/", ft_getenv("USER", ms->envlst)->value);
				tk->str = replace_str(tk->str, ft_strdup("~"), s);
				free(s);
			}
			else
				tk->str = replace_str(tk->str, ft_strdup("~"), home->value);
		}
		else if (tk->str && ft_strchr(tk->str, '~'))
			tk->type = CH_NORMAL;
		tk = tk->next;
	}
}
