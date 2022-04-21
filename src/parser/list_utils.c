/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 11:31:42 by obeaj             #+#    #+#             */
/*   Updated: 2022/04/21 16:46:38 by obeaj            ###   ########.fr       */
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

t_token	**del_token(t_token **tok, t_token *token)
{
	t_token	*first;
	int		len;

	first = *tok;
	len = ft_strlen(token -> data);
	while (first)
	{
		if (first -> tok == token -> tok)
			break ;
		first = first -> next;
	}
	first -> prev -> next = first -> next;
	first -> next -> prev = first -> prev;
	free(first -> data);
	free(first);
	return (tok);
}

void	del_token_0(t_token *token)
{
	token -> prev -> next = token -> next;
	token -> next -> prev = token -> prev;
	free(token -> data);
	free(token);
}

t_token	**token_init(t_token **token)
{
	token = malloc(sizeof(t_token **));
	if (!token)
		return (NULL);
	*token = NULL;
	return (token);
}

t_token	*new_token(t_tok tok, char *data)
{
	t_token	*token;

	token = malloc(sizeof(t_token) * 1);
	token -> data = data;
	token -> tok = tok;
	token -> next = NULL;
	token -> prev = NULL;
	return (token);
}
