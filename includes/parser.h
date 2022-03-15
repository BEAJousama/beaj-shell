/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:45:33 by obeaj             #+#    #+#             */
/*   Updated: 2022/03/15 20:10:09 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "minishell.h"
// # define PIPE '|'
// # define LTHAN '<'
// # define GTHAN '>'
// # define GGTHAN ">>"
// # define HDOC  "<<"
// # define BACK  '&'
// # define AND  "&&"
// # define SEMIC  ';'
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
	REDIR = (OR | LTH | GGTH | GTH), 
}	t_tok;

typedef struct s_token
{
	t_tok 	tok;
	char	*type;
	char	*data;
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
#endif

