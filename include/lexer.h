#ifndef LEXER_H
# define LEXER_H

enum e_tokens {
	CHAR_PIPE = '|',
	CHAR_AMPERSAND = '&',
	CHAR_SQUOTE = '\'',
	CHAR_DQUOTE = '\"',
	CHAR_SEMICOL = ';',
	CHAR_SPACE = ' ',
	CHAR_ESCAPE = '\\',
	CHAR_NL = '\n',
	CHAR_TAB = '\t',
	CHAR_GREAT = '>',
	CHAR_LESS = '<',
	CHAR_NORMAL = -1,
	CHAR_NULL = 0,
};

typedef struct s_token
{
	int		type;
	char	*str;
	t_token	*next;
} t_token;


#endif