/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 18:11:25 by obeaj             #+#    #+#             */
/*   Updated: 2022/04/27 18:12:11 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*parselist(t_token **tokens)
{
	t_cmd	*cmd;
	t_split	sp;

	sp = find(tokens, BG | SC, 0);
	cmd = new_ast_node(sp.tok);
	if (!cmd)
		return (NULL);
	cmd -> right = parseline(sp.right);
	cmd -> left = parseline(sp.left);
	return (cmd);
}

t_cmd	*parsecondition(t_token **tokens)
{
	t_cmd	*cmd;
	t_split	sp;

	sp = find(tokens, OR | AND, 0);
	cmd = new_ast_node(sp.tok);
	if (!cmd)
		return (NULL);
	cmd -> right = parseline(sp.right);
	cmd -> left = parseline(sp.left);
	return (cmd);
}

t_cmd	*parsepipe(t_token **tokens)
{
	t_cmd	*cmd;
	t_split	sp;

	sp = find(tokens, PP, 0);
	cmd = new_ast_node(PP);
	if (!cmd)
		return (NULL);
	cmd -> right = parseline(sp.right);
	cmd -> left = parseline(sp.left);
	return (cmd);
}

t_cmd	*parseblock(t_token **tokens)
{
	t_cmd	*cmd;
	t_split	sp;

	sp = find(tokens, OPR, 1);
	cmd = new_ast_node(OPR);
	if (!cmd)
		return (NULL);
	cmd -> left = NULL;
	cmd -> right = parseline(sp.right);
	return (cmd);
}
