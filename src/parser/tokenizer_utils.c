/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 02:51:48 by obeaj             #+#    #+#             */
/*   Updated: 2022/04/20 14:36:06 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenize_1(char **line, t_token **tok)
{
	char		val[3];
	t_tokenizer	t;

	(t.s) = *line;
	t.tok1 = (*t.s == '|') * PP + (*t.s == '>') * GTH + (*t.s == '<') * LTH \
		+ (*t.s == '&') * BG + (*t.s == '(') * OPR + (*t.s == ')') * CPR \
		+ (*t.s == ';') * SC;
	(t.s)++;
	t.tok2 = (*t.s == '|') * OR + (*t.s == '>') * GGTH + (*t.s == '<') * HDOC \
		+ (*t.s == '&') * AND + (*t.s == ';') * DSC;
	if (t.tok1 & (OPR | CPR | QT | DQT))
	{		
		val[0] = *((t.s - 1));
		val[1] = 0;
		add_token_back(tok, new_token(t.tok1, ft_strdup(val)));
	}
	if (t.tok1 & (PP | GTH | LTH | BG | SC))
	{
		if (t.tok2 && *t.s == *(t.s - 1))
		{
			val[0] = *(t.s - 1);
			val[1] = *(t.s - 1);
			val[2] = 0;
			add_token_back(tok, new_token(t.tok2, ft_strdup(val)));
			t.s++;
		}
		else
		{
			val[0] = *((t.s - 1));
			val[1] = 0;
			add_token_back(tok, new_token(t.tok1, ft_strdup(val)));
		}
	}
	while (*t.s && ft_strchr(SPACES, *t.s))
		t.s++;
	*line = (t.s);
}

void	tokenize_3(char **line, t_token **tok)
{
	int		len;
	char	*s;
	int		check;

	s = *line;
	check = 1;
	len = 1;
	add_token_back(tok, new_token(DQT, ft_strdup("\"")));
	if (*(s + 1) == '\"')
	{
		add_token_back(tok, new_token(STR, ft_strdup("")));
		add_token_back(tok, new_token(DQT, ft_strdup("\"")));
		*line += 2;
		return ;
	}
	s++;
	while (*s && *s != '\n' && *s != '\"')
	{
		if (*s == '$')
		{
			if (len > 1)
				add_token_back(tok, new_token(STR, ft_strndup(*line + 1, len)));
			*line = tokenize_4(&s, tok);
			s = *line;
			len = 0;
		}
		else if (*s == '\\')
		{
			if (len > 1)
				add_token_back(tok, new_token(STR, ft_strndup(*line + 1, len)));
			*line = tokenize_6(&s, tok);
			s = *line;
			check = 0;
			len = 1;
		}
		else
		{
			len++;
			s++;
		}
	}
	if (len > 1)
		add_token_back(tok, new_token(STR, ft_strndup(*line + check, len)));
	if (*s == '\"')
	{
		add_token_back(tok, new_token(DQT, ft_strdup("\"")));
		s++;
	}
	*line = s;
}
