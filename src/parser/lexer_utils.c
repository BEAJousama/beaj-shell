/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 02:54:13 by obeaj             #+#    #+#             */
/*   Updated: 2022/03/31 03:19:20 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	**concat_words_utils(t_token **tokens, t_token *token)
{
	t_token	*sec;
	sec = token -> next;
	while (sec -> tok & STR)
	{
		token -> data = ft_strjoin(token -> data, sec -> data);
		sec = sec -> next;
	}
	return (tokens);
}

void	del_unused(t_token **tokens)
{
	t_token	*first;
	t_token	*sec;
	
	first = *tokens;
	while (first)
	{
		if (first -> tok & STR)
		{
			sec = first -> next;
			while (sec -> tok & STR)
			{
				del_token_0(sec);
				sec = sec -> next;
			}
		}
		first = first -> next;
	}
}

t_token	**concat_words(t_token **tokens)
{
	t_token *first;
	t_token	*sec;
	
	first = *tokens;
	while (first)
	{
		if (first -> tok == STR)
			tokens = concat_words_utils(tokens, first);
		first = first -> next;
	}
	del_unused(tokens);
	return (tokens);
}

t_token	**quotes_filter(t_token **tokens)
{
	t_token	*first;
	t_token	*todel;
	
	first = *tokens;
	while (first)
	{
		if (first -> tok & (QT | DQT))
		{
			todel = first;
			first = first -> next;
			del_token(tokens, todel);
		}
		else
			first = first -> next;
	}
	return (tokens);
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