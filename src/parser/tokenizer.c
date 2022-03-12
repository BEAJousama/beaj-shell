/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:46:21 by obeaj             #+#    #+#             */
/*   Updated: 2022/03/12 19:30:30 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	peek(char **line, char *eline, char *toks)
{
  char	*s;

  s = *line;
  while (s < eline && ft_strchr(SPACES, *s))
    s++;
  *line = s;
  return (*s && ft_strchr(toks, *s));
}

char	tokenizer(char **line, char *eline, char **tok, char **etok)
{
	char	*s;
	char	r;
		
	s = *line;
	while (s < eline && ft_strrchr(SPACES, *s))
		s++;
	if (!*s)
		return (0);
	if (*tok)
		*tok = ft_strdup(s);
	r = *s;
	if (ft_strchr(TERMES_1, *s))
		s++;
	else if (*s == '>')
	{
		s++;
		if (*s == '>')
			r = '+';
		s++;
	}
	else if (*s == '<')
	{
		s++;
		if (*s == '<')
			r = '-';
		s++;
	}
	else if (*s == '|')
	{
		s++;
		if (*s == '|')
			r = '*';
		s++;
	}
	else if (*s == '&')
	{
		s++;
		if (*s == '&')
			r = '#';
		s++;
	}
	else
	{
		r = 'o';
		while (s < eline)
		{
			if (ft_strchr(TERMES, *s))
				break ;
			s++;
		}
	}
	if (etok)
		*etok = s--;
	// **etok = '\0';
	*line = ++s;
	return (r);
}

t_token	*new_token()
{
	t_token	*tok;
	
	tok = malloc(sizeof(t_token) * 1);
	tok-> next = NULL;
	tok-> prev = NULL;
	return(tok);
}

void	add_token_back(t_token **tok, t_token *newtok)
{
	t_token *first;
	
	if (!tok)
		return ;
	if (*tok)
	{
		first = *tok;
		while (first -> next)
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
	newtok -> next = (*tok);
	(*tok) -> prev = newtok;
	*tok = newtok;
}

t_token *gettoken(char **ln, char *eln)
{
	t_token		*token;
	char **tok; 
	char **etok;
	char	c;

	tok = malloc(sizeof(char *));
	etok = malloc(sizeof(char *));
	*tok = malloc(sizeof(char ));
	*etok = malloc(sizeof(char ));
	token = malloc(sizeof(t_token) * 1);;
	token ->next = NULL;
	token ->prev = NULL;
	c = tokenizer(ln, eln, tok, etok);
	if ( c == '|')
		token->type = ft_strdup("PIPE");
	else if (c == '+')
		token->type = ft_strdup("GGTHAN");
	else if (c == '>')
		token->type = ft_strdup("GTHAN");
	else if (c == '<')
		token->type = ft_strdup("LTHAN");
	else if (c == '-')
		token->type = ft_strdup("HDOC");
	else if (c == '*')
		token->type = ft_strdup("OR");
	else if (c == '&')
		token->type = ft_strdup("BACK");
	else if (c == '#')
		token->type = ft_strdup("AND");
	else if (c == '(')
		token->type = ft_strdup("OPAR");
	else if (c == ')')
		token->type = ft_strdup("CPAR");
	else if (c == ';')
		token->type = ft_strdup("SEMIC");
	else if (c == 'o')
		token->type = ft_strdup("WORD");
	else if (c == '\'')
		token->type = ft_strdup("SQUOT");
	else if (c == '\"')
		token->type = ft_strdup("DQUOT");
	token->data = ft_strdup(*tok);
	return(token);
}

t_token **tokens(char **line, char *eline)
{
	t_token	**token;
	int	i;
	
	i = 0;
	token = malloc(sizeof(t_token *) * 1);
	*token = gettoken(line, eline);	
	while(**line)
	{	
		add_token_back(token, gettoken(line, eline));
		i++;
	}
	return (token);
}

int main()
{
	char **line;
	char *eline;
	t_token **toks;
	
	line = malloc(sizeof(char *));
	*line = ft_strdup("(ls -la) || grep \".c\" && cat file.txt > ls -la >> ls | > txt.txt ; cat txt.txt &");
	eline = *line + ft_strlen(*line);
	toks = tokens(line, eline);
	int i = 0;
	while ((*toks))
	{
		printf("%s ---->\n ", (*toks)->data);
		(*toks) = (*toks)-> next;
	}
}