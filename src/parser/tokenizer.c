/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:46:21 by obeaj             #+#    #+#             */
/*   Updated: 2022/04/29 21:30:49 by obeaj            ###   ########.fr       */
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
	else if (*s == '\n' || ft_strchr(SPACES, *s) || *s == '\"')
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

void	tokenize_5(char **line, t_token **tok)
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

t_token	**tokenizer(char **line, char *charset)
{
	t_token	**token;
	char	*s;

	s = NULL;
	token = NULL;
	token = token_init(token);
	*token = new_token(CMDBEG, ft_strdup(""));
	while (**line)
	{
		if (peek(line, SPACES))
			tokenize_0(line, token);
		else if (**line == '\'')
			tokenize_2(line, token);
		else if (**line == '"')
			tokenize_3(line, token, 1, 1);
		else if (**line == '\\' && !ft_isalnum(*(*line + 1)))
			tokenize_6(line, token);
		else if (peek(line, "$"))
			*line = tokenize_4(line, token);
		else if (peek(line, charset))
			tokenize_1(line, token);
		else
			tokenize_5(line, token);
	}
	return (token);
}

void print_tree(t_cmd *c)
{
	if (c)
	{
		printf("----%d----\n", c ->type);
	}
	else
		return ;
	if (c -> right)
	{
		puts("right : \n");
		print_tree(c->right);
	}
	if (c -> left)
	{
		puts("left : \n");
		print_tree(c->left);
	}
}

// int	main(int ac, char **av, char **env)
// {
// 	char	**line;
// 	char	*s;
// 	t_token	**toks;
// 	t_token	*first;
	
// 	(void)av;
// 	(void)ac;

// 	line = malloc(sizeof(char *));
// 	s = *line;
// 	*line = readline("obeaj->");
// 	toks = lexer(line, env);
// 	if (!toks)
// 		return 0;
// 	first = *toks;
// 	// t_cmd **cmd;
// 	// cmd = parsing(toks);
// 	// if (!cmd)
// 	// 	return 0;
// 	// runcmd(*cmd);
// 	// while (*cmd) 
// 	// {
// 	// 	printf ("%d\n", (*cmd)->type);
// 	// 	// if ((*cmd)->type & AST_EXEC)
// 	// 	// 	printf ("%s\n", (*cmd)->argv[0]);	
// 	// 	// if ((*cmd)->type & AST_REDIR)
// 	// 	// 	printf ("%s\n", (*cmd)->file);	
// 	// 	*cmd = (*cmd) -> right;	
// 	// }
// 	// print_tree(*cmd);
// 	while (first)
// 	{
// 		printf("%s ----> %u\n", first->data, first->tok);
// 		if (first -> tok & WC && first -> group)
// 		{
// 			while (*first -> group)
// 			{
// 				printf("######## %s ###########\n", (*first->group)-> data);
// 				(*first -> group) = (*first -> group)-> next;
// 			}
// 		}
// 		first = first-> next;
// 	}
// 	// free(line);
// 	// free_tokens(toks);
// 	// free_glob();
// 	// free(*cmd);
// 	// free(cmd);
// }

