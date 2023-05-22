#include "lexer.h"
#include "minishell.h"
#include "libft.h"
#include "fractol_utils.h"
#include "ft_printf.h"

t_envlst	*get_var_env(char *str, t_ms *ms)
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
		while (word[i] && word[i] != '\0' && \
			(ft_isalnum(word[i]) || word[i] == '_'))
			i++;
		v_name = ft_substr(word, 1, i - 1);
		env_variable = ft_getenv(v_name, ms->envlst);
		free(v_name);
	}
	return (env_variable);
}

char	*replace_str(char *og, char *find, char *repl)
{
	int		final_len;
	char	*str;
	int		i;
	int		j;

	final_len = ft_strlen(og) + ft_strlen(repl) - ft_strlen(find);
	str = ft_calloc(final_len + 1, sizeof(char));
	i = ft_strnstr(og, find, ft_strlen(og)) - og;
	j = -1;
	while (++j < i)
		str[j] = og[j];
	ft_strlcat(str, repl, final_len + 1);
	j = i + ft_strlen(repl);
	i += ft_strlen(find) - 1;
	while (og[i++] != '\0')
		str[j++] = og[i];
	free(og);
	free(find);
	return (str);
}

char	*get_var_name(char *str)
{
	char	*word;
	char	*v_name;
	int		i;

	v_name = NULL;
	word = ft_strchr(str, '$');
	if (word)
	{
		i = 1;
		while (word[i] && word[i] != '\0' && \
			(ft_isalnum(word[i]) || word[i] == '_' || word[i] == '?'))
			i++;
		if (i == 1)
			return (0);
		v_name = ft_substr(word, 0, i);
	}
	return (v_name);
}
