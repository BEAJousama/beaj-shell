/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 12:32:11 by obeaj             #+#    #+#             */
/*   Updated: 2022/04/25 01:29:02 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_glob	g_glob;

t_tok	redir_tok(t_token *token)
{
	t_tok	tok;

	tok = 0;
	if ((token -> tok & GTH) & GTH)
		tok = GTH;
	else if ((token ->tok & GGTH) & GGTH)
		tok = GGTH;
	else if ((token ->tok & LTH) & LTH)
		tok = LTH;
	else if ((token ->tok & HDOC) & HDOC)
		tok = HDOC;
	return (tok);
}

t_cmd	*parseredir(t_cmd *cmd, t_token **tokens)
{	
	t_cmd	*cmd1;
	t_tok	token;

	if ((*tokens)->tok & CMDEND)
		return (cmd);
	cmd1 = cmd;
	if ((*tokens)-> tok & REDIR)
	{
		token = redir_tok(*tokens);
		cmd1 = new_redir_node(cmd1, tokens, token);
		if (!cmd1)
			return (cmd);
	}
	return (cmd1);
}

t_cmd	*parsecmd(t_token **tokens)
{
	t_cmd	*cmd;
	t_token	*first;
	int		ac;

	cmd = NULL;
	ac = 0;
	if (!*tokens)
		return (NULL);
	first = *tokens;
	cmd = new_exec_node(cmd, tokens);
	cmd = parseredir(cmd, tokens);
	while (!(first -> tok & CMDEND))
	{
		cmd = parseredir(cmd, &first);
		first = first -> next;
	}
	cmd -> argv[ac] = 0;
	return (cmd);
}
/*int g_n = 0;*/

t_cmd	*parseline(t_token **tokens)
{
	t_cmd	*cmd;

	if (is_there(tokens, SC | BG, 0))
		cmd = parselist(tokens);
	else if (is_there(tokens, OR | AND, 0))
		cmd = parsecondition(tokens);
	else if (is_there(tokens, PP, 0))
		cmd = parsepipe(tokens);
	else if (is_there(tokens, OPR, 1))
		cmd = parseblock(tokens);
	else
		cmd = parsecmd(tokens);
	return (cmd);
}

t_cmd	**parsing(t_token **tokens)
{
	t_cmd	**cmd;
	t_token	*tok;

	cmd = malloc(sizeof(t_cmd *));
	if (!cmd)
		return (NULL);
	tok = *tokens;
	if (!tok || !tokens)
		return (NULL);
	*cmd = parseline(tokens);
	return (cmd);
}
