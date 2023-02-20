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
	CH_LESS = '<',
	CHAR_GREATGREAT,
	CHAR_LESSLESS,
	CHAR_DELIMITER,
	CHAR_NORMAL = -1,
	CHAR_NULL = 0,
};

enum e_status {
	NORMAL,
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

/* parser/lexer.c */
void	debug_tokenize(char *input);

/* parser/lexer_utils.c */
void	lexer_init(char *input, t_token *token);
void	lexer_free(t_lexer *lexer);

/* parser/tokens.c */
void	trim_quotes_token(t_token *token);
int		close_quotes(t_token *token, char quote_char);
t_token	*other_tokens(t_token *token, int type, int *j, int len);
void	compund_tokens(t_token *token);
t_token	*escape_token(t_token *token, char *input, int *j, int *i);

/* parser/tokens_utils.c */
int		get_token_type(char c);
t_token	*token_init(t_token *token, int size);
void	token_free(t_token *token);
void	remove_empty_tokens(t_token	*token);

#endif