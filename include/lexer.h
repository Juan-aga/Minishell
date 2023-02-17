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

enum e_status {
	NORMAL,
	DOUBLE_QUOTE,
	SINGLE_QUOTE,
	ESCAPED,
};

typedef	struct s_token t_token;

typedef struct s_token
{
	int		type;
	char	*str;
	int		status;
	t_token	*next;
} t_token;

typedef struct s_lexer
{
	t_token	*token_list;
	int		n_tokens;
} t_lexer;

int		ft_get_token_type(char c);
t_token	*token_init(t_token *token, int size);
void	token_free(t_token *token);
void	lexer_free(t_lexer *lexer);
void	debug_tokenize(char *input);
void	clean_tokens(t_token *token);

#endif