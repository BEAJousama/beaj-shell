/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:46:21 by obeaj             #+#    #+#             */
/*   Updated: 2022/03/17 19:52:48 by obeaj            ###   ########.fr       */
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

void	del_token(t_token **tok, t_token *token)
{
	t_token	*first;
	int		len;

	first = *tok;
	len = ft_strlen(token -> data);
	while (first -> next)
	{
		if (!ft_strncmp(first -> data, token -> data, len)
			&& first -> tok == token -> tok)
			break ;
		first = first -> next;
	}
	first -> prev -> next = first -> next;
	first -> next -> prev = first -> prev;
	first -> prev = NULL;
	first -> next = NULL;
	free(first -> data);
	free (first);
}

// void analyzer(t_token **tokens)
// {
// 	t_token	*first;
// 	t_token	*right;
// 	t_token	*left;

// 	first = *tokens;
// 	while (first)
// 	{
// 		right = first -> next;
// 		left = first -> prev; 
// 		if (first -> tok == OPR)
// 		{
// 			if (right->tok != OPR  && right->tok != STR
// 				&& right->tok != GTH && right->tok != GGTH
// 				&& right->tok != LTH && right->tok != HDOC)
// 			{
// 				perror("SYntax Error");
// 				printf ("  at %c\n", right ->data[0]);
// 			}
// 			if (left->tok != AND && left->tok != OR
// 				&& left->tok != PP && left->tok != OPR)
// 			{
// 				perror("SYntax Error");
// 				printf ("  at %c\n", left ->data[0]);
// 			}
// 		}
// 		else if(first->tok == CPR)
// 		{
// 			if (right->tok != CPR && right->tok != STR)
// 			{
// 				perror("SYntax Error");
// 				printf ("  at %c\n", right ->data[0]);
// 			}
// 			if (left->tok != AND && left->tok != OR
// 				&& left->tok != PP && left->tok != CPR
// 				&& left->tok != SC)
// 			{
// 				perror("SYntax Error");
// 				printf ("  at %c\n", left ->data[0]);
// 			}
// 		}
// 		else if(first->tok == GTH || first->tok == GGTH
// 				|| first->tok == LTH || first->tok == HDOC)
// 		{
// 			if (right->tok != STR)
// 			{
// 				perror("SYntax Error");
// 				printf ("  at %c\n", right ->data[0]);
// 			}
// 		}
// 		else if(first->tok == AND || first->tok == OR
// 				|| first->tok == PP)
// 		{
// 			if (right->tok != CPR && right->tok != STR)
// 			{
// 				perror("SYntax Error");
// 				printf ("  at %c\n", right->data[0]);
// 			}
// 			if (right->tok != OPR && right->tok != STR
// 				&& right->tok != GTH && right->tok != GGTH
// 				&& right->tok != LTH && right->tok != HDOC)
// 			{
// 				perror("SYntax Error");
// 				printf ("  at %c\n", left->data[0]);
// 			}
// 		}
// 		first = first -> next;
// 	}
// }

t_token	*new_token(t_tok tok, char *data)
{
	t_token	*token;

	token = malloc(sizeof(t_token) * 1);
	token -> tok = (t_tok)malloc(sizeof(t_tok) * 1);
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
		+ (*t.s == ';') * SC + (*t.s == '\'') * QT + (*t.s == '\"') * DQT;
	(t.s)++;
	t.tok2 = (*t.s == '|') * OR + (*t.s == '>') * GGTH + (*t.s == '<') * HDOC \
		+ (*t.s == '&') * AND + (*t.s == ';') * DSC;
	if (t.tok2)
	{
		val[0] = *(t.s - 1);
		val[1] = *(t.s - 1);
		val[2] = 0;
		add_token_back(tok, new_token(t.tok2, val));
		t.s++;
	}
	else if (t.tok1)
	{
		val[0] = *((t.s) - 1);
		val[1] = 0;
		add_token_back(tok, new_token(t.tok1, val));
	}
	*line = (t.s);
}

void	tokenize2(char **line, char *eline, t_token **tok)
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
		if (ft_strchr("<>&\'\";()|", *s))
			break ;
		s++;
		len++;
	}
	copy[len] = '\0';
	add_token_back(tok, new_token(tok1, copy));
	*line = s;
	free(copy);
}

void	data_filtering(t_token **token)
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
				if (ft_strchr("<>&\'\";()|", first->data[i]))
				{
					first->data[i] = 0;
				}
				i++;
			}
		}
		first = first -> next;
	}
}

t_token	**tokens(char **line, char *eline)
{
	t_token	**token;
	t_tok	tok;

	token = malloc(sizeof(t_token *) * 1);
	tok = CMDBEG;
	*token = new_token(tok, "\0");
	while (*line[0])
	{
		if (peek(line, eline, "<>&\'\";()|"))
			tokenize1(line, eline, token);
		else
			tokenize2(line, eline, token);
	}
	add_token_back(token, new_token(CMDEND, "\0"));
	data_filtering(token);
	return (token);
}

int	main(int ac, char **av, char **env)
{
	char	**line;
	char	*eline;
	t_token	**toks;

	line = malloc(sizeof(char *));
	*line = ft_strdup("((\'cat\' *.c)) || cat file.txt > \"file1.txt\" || gcc -c main.c ;");
	eline = *line + ft_strlen(*line);
	toks = tokens(line, eline);
	syntax_analyse(toks);
	// expand()
	while ((*toks) -> next)
	{
		// printf("%s ---->\n", (*toks)->data);
		(*toks) = (*toks)-> next;
	}
	while ((*toks))
	{
		printf("%s ---->\n", (*toks)->data);
		(*toks) = (*toks)-> prev;
	}
}
