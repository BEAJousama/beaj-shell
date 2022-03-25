/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:46:21 by obeaj             #+#    #+#             */
/*   Updated: 2022/03/25 16:59:41 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_token_back(t_token **tok, t_token *newtok)
{
	t_token	*first;

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

void	insert_token(t_token **tok, t_token *newtok, int pos)
{
	t_token	*first;
	int		i;
	
	first = *tok;
	i = 0;
	while (first && i < pos)
	{
		first = first -> next;
		i++;
	}
	add_token_back(tok, newtok);
}

void	add_token_front(t_token **tok, t_token *newtok)
{	
	if (!tok)
		return ;
	if (*tok)
	{
		(*tok)-> prev = newtok;
		newtok -> next = (*tok);
		*tok = newtok;
	}
	else
		*tok = newtok;
}

t_token	**del_token(t_token **tok, t_token *token)
{
	t_token	*first;
	int		len;

	first = *tok;
	len = ft_strlen(token -> data);
	while (first)
	{
		if (!ft_strncmp(first -> data, token -> data, len)
			&& (first -> tok == token -> tok))
			break ;
		first = first -> next;
	}
	first -> prev -> next = first -> next;
	first -> next -> prev = first -> prev;
	free(first -> data);
	free (first);
	return (tok);
}

void	free_tokens(t_token **tokens)
{
	t_token	*first;
	
	first = NULL;
	while (*tokens)
	{
		first = (*tokens)-> next;
		free((*tokens)->data);
		free(*tokens);
		(*tokens) = first;
	}
	free(tokens);
}

t_token	*new_token(t_tok tok, char *data)
{
	t_token	*token;

	token = malloc(sizeof(t_token) * 1);
	token -> data = ft_strdup(data);
	token -> tok = tok;
	token -> next = NULL;
	token -> prev = NULL;
	return (token);
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
	t.tok1 = (*t.s == '|') * PP + (*t.s == '>') * GTH + (*t.s == '<') * LTH \
		+ (*t.s == '&') * BG + (*t.s == '(') * OPR + (*t.s == ')') * CPR \
		+ (*t.s == ';');
	(t.s)++;
	t.tok2 = (*t.s == '|') * OR + (*t.s == '>') * GGTH + (*t.s == '<') * HDOC \
		+ (*t.s == '&') * AND + (*t.s == ';') * DSC;
	if (t.tok1 & (OPR | CPR | QT | DQT))
	{		
		val[0] = *((t.s - 1));
		val[1] = 0;
		add_token_back(tok, new_token(t.tok1, val));
	}
	if (t.tok1 & (PP | GTH | LTH | BG | SC))
	{
		if (t.tok2 && *t.s == *(t.s - 1))
		{
			val[0] = *(t.s - 1);
			val[1] = *(t.s - 1);
			val[2] = 0;
			add_token_back(tok, new_token(t.tok2, val));
			t.s++;
		}
		else
		{
			val[0] = *((t.s - 1));
			val[1] = 0;
			add_token_back(tok, new_token(t.tok1, val));	
		}
	}
	while (*t.s && ft_strchr(SPACES, *t.s))
		t.s++;
	*line = (t.s);
}

void	tokenize2(char **line, char *eline, t_token **tok, char *charset)
{
	char	*s;
	char	*copy;
	int		len;
	t_tok	tok1;

	s = *line;
	tok1 = STR;
	copy = ft_strdup(*line);
	while (*s)
	{
		if (ft_strchr(charset, *s) && *s != ' ')
			break ;
		s++;
		len++;
	}
	copy[len] = '\0';
	add_token_back(tok, new_token(tok1, copy));
	*line = s;
	free(copy);
}

void	data_filtering(t_token **token, char *charset)
{
	t_token	*first;
	int		i;

	first = *token;
	while (first->next)
	{
		if (first->tok == STR)
		{
			i = 0;
			while (first->data[i])
			{
				if (ft_strchr(charset, first->data[i]))
				{
					first->data[i] = 0;
				}
				i++;
			}
		}
		first = first -> next;
	}
}


// char	*delete_quotes(char *line)
// {
// 	int	i;
// 	int	j;
// 	char	*copy;
	
// 	i = 0;
// 	j = 0;
// 	while (data[i])
// 	{
// 		if (data[i] == '\"' || data[i] == '\'')
// 		{
// 			j++;
// 		}
// 	}
// }

// t_token	**quotes_filter(t_token **tokens)
// {
// 	t_token	*first;

// 	first = *tokens;
// 	while (first)
// 	{
// 		if (first -> tok == STR)
// 		{
// 			while (first -> data[i])
// 			{
				
// 			}
// 		}
// 		first = first -> next;
// 	}
// 	return (tokens);
// }

t_token	**token_init(t_token **token)
{
	token = malloc(sizeof(t_token **));
	if (!token)
		return (NULL);
	*token = NULL;
	return (token);
}

t_token	**tokens(char **line, char *eline, char *charset)
{
	t_token	**token;
	t_tok	tok;

	token = token_init(token);
	tok = CMDBEG;
	*token = new_token(tok, "\0");
	while (**line)
	{
		if (peek(line, eline, charset))
			tokenize1(line, eline, token);
		else
			tokenize2(line, eline, token, charset);
	}
	add_token_back(token, new_token(CMDEND, "\0"));
	data_filtering(token, charset);
	return (token);
}

void	tokenizing(char **line, char *eline, char *charset)
{
}

void	split_words_args(t_token **tokens)
{
	t_token *first;
	
	first = *tokens;
	while (first)
	{
		if (first -> tok & STR)
		{
			first -> args = ft_split(first -> data, ' ');
		}
		first = first -> next;
	}
}
void	freetab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
	{
		free(tab[i]);
	}
	free(tab);
}
int	main(int ac, char **av, char **env)
{
	char	**line;
	char	*s;
	char	*eline;
	t_token	**toks;
	t_token *first;

	line = malloc(sizeof(char *));
	// *line = ft_strdup("(cat *.c) && > cat ||  \'file.txt\'");
	s = *line;
	// eline = *line + ft_strlen(*line);
	*line = readline("obeaj->");
	toks = tokens(line, eline, "<>&;()|");
	syntax_analyse(toks);
	// toks = tokens(line, eline, "<>&;()| ");
	// expander(tokens);
	// toks = quotes_filter(toks);
	split_words_args(toks);
	first = *toks;
	while (first)
	{
		printf("%s ----> %u\n", first->data, first->tok);
		first = first-> next;
	}
	free_tokens(toks);
}
