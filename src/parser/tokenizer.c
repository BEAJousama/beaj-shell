/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:46:21 by obeaj             #+#    #+#             */
/*   Updated: 2022/03/15 20:15:48 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_token_back(t_token **tok, t_token *newtok)
{
	t_token *first;
	
	if (!tok)
		return ;
	if (*tok)
	{
		first = *tok;
		while (first -> next != NULL)
			first = first -> next;
		newtok -> next = first-> next;
		first -> next = newtok;
		newtok -> prev = first;
	}
	else
		*tok = newtok;
}

void	add_token_front(t_token **tok, t_token *newtok)
{	
	if (!tok)
		return ;
	if (*tok)
	{
		newtok -> next = (*tok);
		(*tok) -> prev = newtok;
		*tok = newtok;
	}
	else
		*tok = newtok;
}

t_token	*new_token(t_tok tok, char *data)
{
	t_token	*token;
	
	token = malloc(sizeof(t_token) * 1);
	token -> tok = (t_tok)malloc(sizeof(t_tok) * 1);
	token -> data = ft_strdup(data);
	token -> tok = tok;
	token -> next = NULL;
	token -> prev = NULL;
	return(token);
}

int	peek(char **line, char *eline, char *toks)
{
  char	*s;

  s = *line;
  while (s < eline && ft_strchr(SPACES, *s))
    s++;
  *line = s;
  return (*s && ft_strchr(toks, *s));
}

void	tokenize1(char **line, char *eline, t_token **tok)
{
	char		val[3];
	t_tokenizer	t;

	(t.s) = *line;
	t.tok1 = (*(t.s) == '|') * PP + (*(t.s) == '>') * GTH + (*(t.s) == '<') * LTH \
		+ (*(t.s) == '&') * BG + (*(t.s) == '(') * OPR + (*(t.s) == ')') * CPR \
		+ (*(t.s) == ';') * SC + (*(t.s) == '\'') * QT + (*(t.s) == '\"') * DQT;
	(t.s)++;
	t.tok2 = (*(t.s) == '|') * OR + (*(t.s) == '>') * GGTH + (*(t.s) == '<') * HDOC \
		+ (*(t.s) == '&') * AND;
		*line = (t.s);
	if (t.tok2)
	{
		val[0] = *(t.s);
		val[1] = *(t.s);
		val[2] = 0;
		add_token_back(tok,  new_token(t.tok2, val));
		(t.s)++;
	}
	else if (t.tok1)
	{
		val[0] = *((t.s) - 1);
		val[1] = 0;
		add_token_back(tok, new_token(t.tok1, val));
	}

}

void	tokenize2(char **line, char *eline, t_token **tok)
{
	char 	*s;
	char	*copy;
	int		len;
	t_tok	tok1;

	s = *line;
	tok1 = STR;
	copy = ft_strdup(*line);
	while (!ft_strchr("<>&\'\";()|", *s))
	{
		s++;
		len++;
	}
	copy[len] = '\0';
	add_token_back(tok, new_token(tok1, copy));
	*line += len;
	printf("%s\n\n\n\n\n", *line);
	free(copy);
}



// char	tokenizer(char **line, char *eline, char **tok, char **etok)
// {
// 	char	*s;
// 	char	r;
		
// 	s = *line;
// 	while (s < eline && ft_strrchr(SPACES, *s))
// 		s++;
// 	if (!*s)
// 		return (0);
// 	if (*tok)
// 		*tok = ft_strdup(s);
// 	r = *s;
// 	if (ft_strchr(TERMES_1, *s))
// 		s++;
// 	else if (*s == '>')
// 	{
// 		s++;
// 		if (*s == '>')
// 			r = '+';
// 		s++;
// 	}
// 	else if (*s == '<')
// 	{
// 		s++;
// 		if (*s == '<')
// 			r = '-';
// 		s++;
// 	}
// 	else if (*s == '|')
// 	{
// 		s++;
// 		if (*s == '|')
// 			r = '*';
// 		s++;
// 	}
// 	else if (*s == '&')
// 	{
// 		s++;
// 		if (*s == '&')
// 			r = '#';
// 		s++;
// 	}
// 	else
// 	{
// 		r = 'o';
// 		while (s < eline)
// 		{
// 			if (ft_strchr(TERMES, *s))
// 				break ;
// 			s++;
// 		}
// 	}
// 	if (etok)
// 		*etok = s--;
// 	// **etok = '\0';
// 	*line = ++s;
// 	return (r);
// }




// t_token *gettoken(char **ln, char *eln)
// {
// 	t_token		*token;
// 	char **tok; 
// 	char **etok;
// 	char	c;

// 	tok = malloc(sizeof(char *));
// 	etok = malloc(sizeof(char *));
// 	*tok = malloc(sizeof(char ));
// 	*etok = malloc(sizeof(char ));
// 	token = malloc(sizeof(t_token) * 1);;
// 	token ->next = NULL;
// 	token ->prev = NULL;
// 	c = tokenizer(ln, eln, tok, etok);
// 	if ( c == '|')
// 		token->type = ft_strdup("PIPE");
// 	else if (c == '+')
// 		token->type = ft_strdup("GGTHAN");
// 	else if (c == '>')
// 		token->type = ft_strdup("GTHAN");
// 	else if (c == '<')
// 		token->type = ft_strdup("LTHAN");
// 	else if (c == '-')
// 		token->type = ft_strdup("HDOC");
// 	else if (c == '*')
// 		token->type = ft_strdup("OR");
// 	else if (c == '&')
// 		token->type = ft_strdup("BACK");
// 	else if (c == '#')
// 		token->type = ft_strdup("AND");
// 	else if (c == '(')
// 		token->type = ft_strdup("OPAR");
// 	else if (c == ')')
// 		token->type = ft_strdup("CPAR");
// 	else if (c == ';')
// 		token->type = ft_strdup("SEMIC");
// 	else if (c == 'o')
// 		token->type = ft_strdup("WORD");
// 	else if (c == '\'')
// 		token->type = ft_strdup("SQUOT");
// 	else if (c == '\"')
// 		token->type = ft_strdup("DQUOT");
// 	token->data = ft_strdup(*tok);
// 	return(token);
// }

t_token **tokens(char **line, char *eline)
{
	t_token	**token;
	t_tok tok;
	int	i;
	
	i = 0;
	token = malloc(sizeof(t_token *) * 1);
	
	// *token = gettoken(line, eline);
	tok = CMDBEG;
	*token = new_token(tok, "\0");
	while(**line)
	{
		if (peek(line, eline, "<>&\'\";()|"))
			tokenize1(line, eline, token);
		else
			tokenize2(line, eline, token);
		// add_token_back(token, gettoken(line, eline));
		// i++;
	}
	return (token);
}

void	data_filtering(t_token **tokens)
{
	
}

int main()
{
	char **line;
	char *eline;
	t_token **toks;
	
	line = malloc(sizeof(char *));
	*line = ft_strdup("<< (ls -la) || grep .c && cat file.txt > ls -la >> ls || > txt.txt ; cat txt.txt &");
	eline = *line + ft_strlen(*line);
	toks = tokens(line, eline);
	int i = 0;
	while ((*toks))
	{
		printf("%s ---->\n", (*toks)->data);
		(*toks) = (*toks)-> next;
	}
}
