/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:46:21 by obeaj             #+#    #+#             */
/*   Updated: 2022/04/16 17:34:12 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenize_0(char **line, t_token **tok)
{
	char	*s;

	s = *line;
	while (*s && ft_strchr(SPACES, *s))
		s++;
	if (*s != **line)
		add_token_back(tok, new_token(WSC, ft_strdup("")));
	*line = s;
}

void	tokenize_2(char **line, t_token **tok)
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
	if (*s == '\'')
	{
		add_token_back(tok, new_token(QT, ft_strdup("\'")));
		s++;
	}
	*line = s;
}

char	*tokenize_4(char **line, t_token **tok)
{
	int		len;
	char	*s;

	len = 0;
	s = *line + 1;
	if (*s == '$' || *s == '?' || ft_isdigit(*s))
	{
		add_token_back(tok, new_token(VAR, ft_strndup(*line + 1, 2)));
		return (*line + 2);
	}
	else if(*s == '\n' || ft_strchr(SPACES, *s) || *s == '\"')
	{
		add_token_back(tok, new_token(STR, ft_strndup(*line, 2)));
		return (*line + 1);
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

void	tokenize_5(char **line, t_token **tok, char *charset)
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
		add_token_back(tok, new_token(TLD,
			ft_strndup(copy, 1 + (copy[1] == '/'))));
	else if (ft_strchr(copy, '*') || ft_strchr(copy, '?'))
		add_token_back(tok, new_token(WC, ft_strdup(copy)));
	else
		add_token_back(tok, new_token(STR, ft_strdup(copy)));
	*line = s;
	free(copy);
}


char	*tokenize_6(char **line, t_token **tok)
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

t_token	**tokens(char **line, char *charset)
{
	t_token	**token;

	token = token_init(token);
	*token = new_token(CMDBEG, ft_strdup(""));
	while (**line)
	{
		if (peek(line, SPACES))
			tokenize_0(line, token);
		else if (**line == '\'')
			tokenize_2(line, token);
		else if (**line == '"')
			tokenize_3(line, token);
		else if (**line == '\\')
			tokenize_6(line, token);
		else if (peek(line, "$"))
			*line = tokenize_4(line, token);
		else if (peek(line, charset))
			tokenize_1(line, token);
		else
			tokenize_5(line, token, charset);
	}
	add_token_back(token, new_token(CMDEND, ft_strdup("")));
	return (token);
}

int	main(int ac, char **av, char **env)
{
	char	**line;
	char	*s;
	t_token	**toks;
	t_token	*first;

	line = malloc(sizeof(char *));
	s = *line;
	*line = readline("obeaj->");
	toks = tokens(line, "<>&;()|");
	syntax_analyse(toks);
	toks = quotes_filter(toks);
	toks = concat_words(toks);
	set_global_env(env);
	toks = expander(toks);
	first = *toks;
	// t_split sp;
	// sp = find(toks, OPR, 1);
	// first = *sp.right;
	while (first && !(first -> tok & CMDEND))
	{
		printf("%s ----> %u\n", first->data, first->tok);
		if (first -> tok & WC && first -> group)
		{
			while (*first -> group)
			{
				printf("######## %s ###########\n", (*first->group)->data );
				(*first -> group) = (*first ->group) -> next;
			}
		}
		first = first-> next;
	}
	// add_global_venv("lolo", "cuuuuute");
	// add_global_venv("PATH", "c123");
	// add_global_venv("A", "");
	// add_global_venv("lolo", "cuuute");
	// del_venv("lolo");
	// show_vars();
	// free_tokens(toks);
}
