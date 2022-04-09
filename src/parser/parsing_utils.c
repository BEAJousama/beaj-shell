/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 01:20:15 by obeaj             #+#    #+#             */
/*   Updated: 2022/04/09 01:20:31 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_token	*escape_block(t_token *first)
{
	int		count;
	t_token	*save;

	save = first;
	count = 0;
	while (save && save -> tok != CMDEND)
	{
		if (save -> tok & OPR)
			count++;	
		save = save -> next;
	}
	while (first && count)
	{
		if (first -> tok & CPR)
			count--;
		first = first -> next;	
	}
	return (first);
}

t_split	find(t_token **tokens, t_tok tok)
{
	t_token	*first;
	t_split	sp;
	
	first = *tokens;
	sp.right = token_init(sp.right);
	sp.left = token_init(sp.left);
	while (first -> tok != CMDEND)
	{
		if (first -> tok & OPR)
			first = escape_block(first);
		if (first -> tok & tok)
			break ;
		first = first -> next;
	}
	if (first -> tok & CMDEND)
		*sp.right = NULL;
	else
		*(sp.right) = first->next;
	free(first -> data);
	first -> tok = CMDEND;
	*(sp.left) = *tokens;
	return (sp);
}