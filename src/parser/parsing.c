/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 12:32:11 by obeaj             #+#    #+#             */
/*   Updated: 2022/03/20 14:26:46 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	**parsing(t_token **tokens)
{
	t_cmd	**cmd;
	t_token	*tok;
	
	tok = *tokens;
	cmd = parseline(tokens, tok);
	return (cmd);
}

t_cmd	**parseline(t_token **tokens, t_token *tok)
{
	t_token *first;
	t_cmd	**tree;
	
	first = *tokens;
	while (first)
	{
		if (first -> tok == PP)
		{
			tree = parseblock(tokens, tok);
		}
	}
}

t_cmd	**parseredir(t_cmd **cmd, t_token **tokens, t_token *tok)
{	
	if (!(tok -> tok & (REDIR)) || tok->next->tok != WORD)
		return (NULL);
	if (tok->tok & LTH)
		cmd = redircmd(cmd, O_RDONLY, tok -> next -> data, 0);
	else if (tok->tok & GTH)
		cmd = redircmd(cmd, O_WRONLY|O_CREAT, tok -> next -> data, 1);
	else if (tok->tok & GGTH)
		cmd = redircmd(cmd, O_WRONLY|O_CREAT|O_APPEND, tok -> next -> data, 1);
	else if (tok->tok & GGTH);
		cmd = redircmd(cmd, O_WRONLY|O_CREAT|O_APPEND, tok -> next -> data, 0)
}