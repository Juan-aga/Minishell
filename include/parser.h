/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 18:32:28 by franmart          #+#    #+#             */
/*   Updated: 2023/06/02 11:57:55 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_ms		t_ms;
typedef struct s_cmdlst	t_cmdlst;
typedef struct s_envlst	t_envlst;

enum e_tokens {
	CH_PIPE = '|',
	CH_SQUOTE = '\'',
	CH_DQUOTE = '\"',
	CH_SPACE = ' ',
	CH_TILDE = '~',
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

t_lexer		*ft_tokenize_line(char *input, t_ms *ms);
void		join_tokens(t_token *token);
void		join_dollars(t_token *token);

/* parser/lexer_utils.c */

void		lexer_init(char *input, t_token *token);
void		lexer_free(t_lexer *lexer);
int			lexer_files(t_token *token);
int			count_tokens(t_lexer *lexer);

/* parser/tokens.c */

int			close_quotes(t_token *tok);
t_token		*other_tokens(t_token *token, int type, int *j, int len);
t_token		*redirect_token(t_token *token, char *input, int *j, int *i);
t_token		*quote_token(t_token *token, int type, int *j, int len);

/* parser/tokens_utils.c */

int			get_token_type(char c);
t_token		*new_token(t_token *token, int size);
void		free_token(t_token *token);
void		remove_empty_tokens(t_lexer	*lexer);
void		trim_quotes_token(t_token *token);

/* parser/expander.c */
t_token		*expand_tokens(t_lexer *lexer, t_ms *ms);
int			replace_next_dollar(char *str, t_ms *ms, t_token *tok);
int			replace_exit_status(t_token *tok, t_ms *ms, char *free_str);
int			replace_dollar_digit(t_token *tok, t_ms *ms, char *free_str);
void		replace_tilde(t_token *tok, t_ms *ms);

/* parser/expander_utils.c */
t_envlst	*get_env_var(char *str, t_ms *ms);
char		*replace_str(char *og, char *find, char *repl);
char		*get_dollar_name(char *str);

/* parser/wildcard_expander.c */
void		expand_all_wildcards(t_lexer *lex);
t_token		*expand_wildcard(t_token *tok, char **wildcards);

/* parser/fill_cmds.c */
void		tokens_to_commands(t_ms *ms, t_lexer *lex);
t_token		*fill_cmd(t_cmdlst *cmd, t_token *tok);
void		get_all_args(t_cmdlst *cmd, t_token *tok);
int			count_args(t_token *tok);
int			open_files_cmd(t_cmdlst *cmd);

#endif
