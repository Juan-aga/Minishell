#include "../include/lexer.h"

int	ft_get_token_type(char c)
{
	if (c == '|')
		return CHAR_PIPE;
	if (c == '&')
		return CHAR_AMPERSAND;
	if (c == '\'')
		return CHAR_SQUOTE;
	if (c == '\"')
		return CHAR_DQUOTE;
	if (c == ';')
		return CHAR_SEMICOL;
	if (c == ' ')
		return CHAR_SPACE;
	if (c == '\\')
		return CHAR_ESCAPE;
	if (c == '\n')
		return CHAR_NL;
	if (c == '\t')
		return CHAR_TAB;
	if (c == '>')
		return CHAR_GREAT;
	if (c == '<')
		return CHAR_LESS;
	if (c == 0)
		return CHAR_NULL;
	return CHAR_NORMAL;
}