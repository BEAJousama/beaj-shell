/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:46:21 by obeaj             #+#    #+#             */
/*   Updated: 2022/04/03 13:50:11 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenize_0(char **line, char *eline, t_token **tok)
{
	char	*s;

	s = *line;
	while (ft_strchr(SPACES, *s))
		s++;
	if (*s != **line)
		add_token_back(tok, new_token(WSC, ft_strdup("")));
	*line = s;
}

void	tokenize_2(char **line, char *eline, t_token **tok)
{
	int		len;
	char	*s;

	s = *line + 1;
	len = 0;
	add_token_back(tok, new_token(QT, ft_strdup("\'")));
	while (*s && *s != '\n' && *s != '\'')
	{
		len++;
		s++;
	}
	add_token_back(tok, new_token(STR, ft_strndup(*line + 1, len + 1)));
	if (*s++ == '\'')
		add_token_back(tok, new_token(QT, ft_strdup("\'")));
	*line = s;
}

char	*tokenize_4(char **line, char *eline, t_token **tok)
{
	int		len;
	char	*s;

	len = 0;
	s = *line + 1;
	if (*s == '$' || *s == '?' || ft_isdigit(*s))
	{
		add_token_back(tok, new_token(VAR, ft_strndup(*line + 1, 2)));
		*line += 2;
		return (*line);
	}
	while (*s && (ft_isalnum(*s) || *s == '_'))
	{
		len++;
		s++;
	}
	add_token_back(tok, new_token(VAR, ft_strndup(*line + 1, len + 1)));
	*line = s;
	return (*line);
}

void	tokenize_5(char **line, char *eline, t_token **tok, char *charset)
{
	char	*s;
	char	*copy;
	int		len;

	s = *line;
	len = 0;
	copy = ft_strdup(*line);
	while (*s)
	{
		if (ft_strchr("<>()|;\'\"$ ", *s))
			break ;
		s++;
		len++;
	}
	copy[len] = '\0';
	if (copy[0] == '~' && (copy[1] == '/' || !copy[1]))
		add_token_back(tok, new_token(TLD, ft_strndup(copy, 1 + (copy[1] == '/'))));
	else if (ft_strchr(copy, '*'))
		add_token_back(tok, new_token(WC, ft_strdup(copy)));
	else
		add_token_back(tok, new_token(STR, ft_strdup(copy)));
	*line = s;
	free(copy);
}


char	*tokenize_6(char **line, char *eline, t_token **tok)
{
	char	*s;
	char	*copy;
	int		len;

	*line += 1;
	s = *line;
	if (!s || !*s)
		return (0);
	len = 1;
	copy = ft_strdup(*line);
	copy[len] = '\0';
	add_token_back(tok, new_token(STR, ft_strdup(copy)));
	*line = s + 1;
	free(copy);
	return (*line);
}

t_token	**tokens(char **line, char *eline, char *charset)
{
	t_token	**token;

	token = token_init(token);
	*token = new_token(CMDBEG, ft_strdup(""));
	while (**line)
	{
		if (peek(line, eline, SPACES))
			tokenize_0(line, eline, token);
		else if (**line == '\'')
			tokenize_2(line, eline, token);
		else if (**line == '"')
			tokenize_3(line, eline, token);
		else if (**line == '\\')
			tokenize_6(line, eline, token);
		else if (peek(line, eline, "$"))
			*line = tokenize_4(line, eline, token);
		else if (peek(line, eline, charset))
			tokenize_1(line, eline, token);
		else
			tokenize_5(line, eline, token, charset);
	}
	add_token_back(token, new_token(CMDEND, ft_strdup("")));
	return (token);
}

int	main(int ac, char **av, char **env)
{
	char	**line;
	char	*s;
	char	*eline;
	t_token	**toks;
	t_token	*first;

	line = malloc(sizeof(char *));
	s = *line;
	*line = readline("obeaj->");
	toks = tokens(line, eline, "<>&;()|");
	syntax_analyse(toks);
	toks = quotes_filter(toks);
	toks = concat_words(toks);
	first = *toks;
	while (first)
	{
		printf("%s ----> %u\n", first->data, first->tok);
		first = first-> next;
	}
	free_tokens(toks);
}
