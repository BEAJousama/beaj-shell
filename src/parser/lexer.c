/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 02:24:10 by obeaj             #+#    #+#             */
/*   Updated: 2022/03/30 03:09:43 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token    **lexer(char **line)
{
    t_token **tokens;
    
    if (!line || !*line || !**line)
		return (NULL);
	if (**line)
		add_history(line);
	tokens = tokenizer(line);
	if (!syntax_analyse(tokens))
		return (NULL);
    tokens = quotes_filter(tokens);
	tokens = expander(tokens);
    return (tokens);
}