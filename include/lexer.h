#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

typedef struct s_ms		t_ms;
typedef struct s_cmdlst	t_cmdlst;
typedef struct s_envlst	t_envlst;

enum e_tokens {
	CH_PIPE = '|',
	CH_AMPERSAND = '&',
	CH_SQUOTE = '\'',
	CH_DQUOTE = '\"',
	CH_SEMICOL = ';',
	CH_SPACE = ' ',
	CH_ESCAPE = '\\',
	CH_LESS = '<',
	CH_GREAT = '>',
	CH_LESSLESS = 63,
	CH_GREATGREAT = 65,
	DELIMITER,
	INFILE,
	OUTFILE,
	OUTFILE_APPEND,
	EXPANDED,
	CH_NORMAL = -1,
	CH_NULL = 0,
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

typedef struct s_token	t_token;

typedef struct s_token
{
	int		type;
	char	*str;
	int		status;
	int		escaped;
	int		join_next;
	t_token	*next;
	t_token	*prev;
}	t_token;

typedef struct s_lexer
{
	t_token	*token_list;
	int		n_tokens;
	int		error;
}	t_lexer;

/* parser/lexer.c */

/* temporary tokenize function, it should be reworked later.
It receives the readline, creates a token list, checks if quotes
are correct and removes empty tokens if any */
t_lexer		*ft_tokenize_line(char *input, t_ms *ms);
void		join_tokens(t_token *token);
void		join_dollars(t_token *token);


/* parser/lexer_utils.c */

/* the lexer_init function is pretty stacked. It reads every char in
input and calls other functions to classify each type of token, creating new
empty tokens when necessary */
void		lexer_init(char *input, t_token *token);
/* frees all tokens in the lexer struct*/
void		lexer_free(t_lexer *lexer);
int			lexer_files(t_token *token);
int			count_tokens(t_lexer *lexer);

/* parser/tokens.c */

/* close_quotes checks if any token in the token list is quoted, and raises an
error if a quoted token is not correct */
int			close_quotes(t_token *tok);
/* this function is stacked too. It classifies all tokens that are not
redirections, normal chars or escape tokens. It removes consecutive espaces,
quotes a token, and allocates a new token if the input is a special char */
t_token		*other_tokens(t_token *token, int type, int *j, int len);
/* this function will be removed as the subject does not require it, but I
thought it was necessary. It escapes special tokens */
t_token		*escape_token(t_token *token, char *input, int *j, int *i);
/* checks the kind of redirection, and if the redirection char is inside quotes,
it treats it as a normal char */
t_token		*redirect_token(t_token *token, char *input, int *j, int *i);
/* checks if the char is a quote and ensures if the open and close quotes are
the same kind */
t_token		*quote_token(t_token *token, int type, int *j, int len);

/* parser/tokens_utils.c */

int			get_token_type(char c);
t_token		*token_init(t_token *token, int size);
void		token_free(t_token *token);
void		remove_empty_tokens(t_lexer	*lexer);
void		trim_quotes_token(t_token *token);

/* parser/expander.c */
void		expand_tokens(t_lexer *lexer, t_ms *ms);
int			replace_next_dollar(char *str, t_ms *ms, t_token *tok);
int			replace_exit_status(t_token *tok, t_ms *ms, char *free_str);
int			replace_next_char(t_token *tok, t_ms *ms, char *free_str);

/* parser/expander_utils.c */
t_envlst	*get_var_value(char *str, t_ms *ms);
char		*replace_env_var(char *og, char *find, char *repl);
char		*get_var_name(char *str);

/* parser/wildcard_expander.c */
void		expand_wildcards(t_lexer *lex);
t_token		*expand_wildcard(t_token *tok, char **wildcards);

/* parser/fill_cmds.c */
void		ft_fill_commands(t_ms *ms, t_lexer *lex);
t_token		*fill_cmd(t_cmdlst *cmd, t_token *tok);
void		get_all_args(t_cmdlst *cmd, t_token *tok);
int			count_args(t_token *tok);
int			open_files_cmd(t_cmdlst *cmd);

#endif
