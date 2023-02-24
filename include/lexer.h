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

enum e_quote_status {
	NO_QUOTE,
	DOUBT_QUOTE,
	SINGLE_QUOTE = '\'',
	DOUBLE_QUOTE = '\"',
};

typedef	struct s_token t_token;

typedef struct s_token
{
	int		type;
	char	*str;
	int		status;
	int		escaped;
	t_token	*next;
} t_token;

typedef struct s_lexer
{
	t_token	*token_list;
	int		n_tokens;
} t_lexer;

/* parser/lexer.c */

/* temporary tokenize function, it should be reworked later.
It receives the readline, creates a token list, checks if quotes
are correct and removes empty tokens if any */
void	debug_tokenize(char *input);

/* parser/lexer_utils.c */

/* the lexer_init function is pretty stacked. It reads every char in
input and calls other functions to classify each type of token, creating new
empty tokens when necessary */
void	lexer_init(char *input, t_token *token);
/* frees all tokens in the lexer struct*/
void	lexer_free(t_lexer *lexer);

/* parser/tokens.c */

/* close_quotes checks if any token in the token list is quoted, and raises an
error if a quoted token is not correct */
int		close_quotes(t_token *tok);
/* this function is stacked too. It classifies all tokens that are not
redirections, normal chars or escape tokens. It removes consecutive espaces,
quotes a token, and allocates a new token if the input is a special char */
t_token	*other_tokens(t_token *token, int type, int *j, int len);
/* this function will be removed as the subject does not require it, but I
thought it was necessary. It escapes special tokens */
t_token	*escape_token(t_token *token, char *input, int *j, int *i);
/* checks the kind of redirection, and if the redirection char is inside quotes,
it treats it as a normal char */
t_token	*redirect_token(t_token *token, char *input, int *j, int *i);
/* checks if the char is a quote and ensures if the open and close quotes are
the same kind */
t_token	*quote_token(t_token *token, int type, int *j, int len);

/* parser/tokens_utils.c */

int		get_token_type(char c);
t_token	*token_init(t_token *token, int size);
void	token_free(t_token *token);
void	remove_empty_tokens(t_token	*token);
void	trim_quotes_token(t_token *token);

#endif