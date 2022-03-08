/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:45:33 by obeaj             #+#    #+#             */
/*   Updated: 2022/03/08 10:44:19 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "minishell.h"
# define PIPE '|'
# define LTHAN '<'
# define GTHAN '>'
# define GGTHAN '>>'
# define HDOC  '<<'
# define BACK  '&'
# define SEMIC  ';'
# define SPACES "\t \v \f \r"
# define TERMES_1 "| ; & ( )"
# define TERMES "> < | ; &"

typedef struct s_token
{
	char	type[10];
	char	val[10];
}	t_token;

char	tokenizer(char **line, char *eline, char **tok, char **etok);

#endif

