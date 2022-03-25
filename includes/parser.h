/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:45:33 by obeaj             #+#    #+#             */
/*   Updated: 2022/03/24 19:25:58 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# define UNEXPECTED_TOK "minishell : syntax error near unexpected token : "
# define UNCLOSED_PAR "minishell :  Unclosed parethesis"
# define UNCLOSED_DQ "minishell :  Unclosed double quotes"
# define UNCLOSED_SQ "minishell :  Unclosed simple quotes"
# define SPACES "\t \v \f \r"

typedef enum s_tok
{
	PP = 1 << 0,
	OR = 1 << 1,
	AND = 1 << 2,
	LTH = 1 << 3,
	GTH = 1 << 4,
	GGTH = 1 << 5,
	HDOC = 1 << 6,
	BG = 1 << 7,
	SC = 1 << 8,
	DR = 1 << 9,
	QT = 1 << 10,
	DQT = 1 << 11,
	OPR = 1 << 12,
	CPR = 1 << 13,
	TLD = 1 << 14,
	STR = 1 << 15,
	CMDBEG = 1 << 16,
	CMDEND = 1 << 17,
	DSC = 1 << 18,
	NL = 1 << 19,
	BIND = (OR | AND | PP),
	BFG = (BG | SC),
	WORD = (STR | QT | DQT),
	REDIR = (HDOC | LTH | GGTH | GTH), 
}	t_tok;

typedef struct s_token
{
	t_tok 	tok;
	char	*type;
	char	*data;
	char	**args;
	struct	s_token	*next;
	struct	s_token	*prev;
}	t_token;

typedef struct s_tokenizer
{
	t_tok	tok1;
	t_tok	tok2;
	char	*s;
}	t_tokenizer;
typedef struct s_cmdline
{
	char	**line;
	char	*eline;
	char	**tok;
	char	**etok;
}	t_cmdline;

char	tokenizer(char **line, char *eline, char **tok, char **etok);
int		print_error(char *str, char *data);
void	add_token_back(t_token **tok, t_token *newtok);
void	insert_token(t_token **tok, t_token *newtok, int pos);
void	add_token_front(t_token **tok, t_token *newtok);
t_token	**del_token(t_token **tok, t_token *token);
t_token	*new_token(t_tok tok, char *data);
int		peek(char **line, char *eline, char *toks);
void	tokenize1(char **line, char *eline, t_token **tok);
void	tokenize2(char **line, char *eline, t_token **tok, char *charset);
void	data_filtering(t_token **token, char *charset);
t_token	**tokens(char **line, char *eline, char *charset);
int		check_par_match(t_token **tokens);
int		check_quotes_match(t_token **tokens);
int		check_parethesis(t_token **tokens);
int		check_binders(t_token **tokens);
int		check_redirect(t_token **tokens);
int		syntax_analyse(t_token **tokens);
char	*ft_strjoin1(char *s1, char *s2);
#endif

