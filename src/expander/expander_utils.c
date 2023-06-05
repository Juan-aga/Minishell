/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 18:22:36 by franmart          #+#    #+#             */
/*   Updated: 2023/05/22 18:22:38 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Given a token, searchs for a valid dollar variable and returns its
envlst node. Return NULL if can't find it */

t_envlst	*get_env_var(char *str, t_ms *ms)
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

/* Find and replace function. Given a string to find "find" in "og", it replaces
every coincidence for the "repl" string. For convenience and to reduce function
lines elsewhere, it frees both original string and the "find" string */

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

/* Given a string, return a substring with the dollar variable name */

char	*get_dollar_name(char *str)
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
