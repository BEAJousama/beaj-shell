/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 02:24:10 by obeaj             #+#    #+#             */
/*   Updated: 2022/04/29 16:28:17 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	**lexer(char **line, char **env)
{
	t_token	**tokens;

	(void)env;
	if (!line || !*line || !**line)
		return (NULL);
	if (**line)
		add_history(*line);
	tokens = tokenizer(line, "<>&;()|");
	if (!tokens)
		return (NULL);
	add_token_back(tokens, new_token(CMDEND, ft_strdup("newline")));
	if (syntax_analyse(tokens))
		return (NULL);
	g_glob.vars = set_global_vars(g_glob.vars);
	tokens = quotes_filter(tokens);
	tokens = concat_words(tokens);
	tokens = expander(tokens);
	return (tokens);
}
