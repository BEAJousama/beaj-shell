/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 12:32:11 by obeaj             #+#    #+#             */
/*   Updated: 2022/04/09 01:55:48 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_glob glob;


t_cmd	*parselist(t_token **tokens)
{
	t_cmd	*cmd;
	
	cmd = newlistnode();
	cmd -> right = parseline(right_toks);
	cmd -> left = parseline(right_toks);
	return cmd;
}

t_cmd	*parsecondition(t_token **tokens)
{
	t_cmd	*cmd;
	
	cmd = newlistnode();
	cmd -> right = parseline(right_toks);
	cmd -> left = parseline(right_toks);	
	return cmd;
}

t_cmd	*parsepipe(t_token **tokens)
{
	t_cmd	*cmd;
	
	cmd = newlistnode();
	cmd -> right = parseline(right_toks);
	cmd -> left = parseline(right_toks);	
	return cmd;
}

t_cmd	*parseredir(t_token **tokens)
{
	t_cmd	*cmd;
	
	cmd = newlistnode();
	cmd -> right = parseline(right_toks);
	cmd -> left = parseline(right_toks);	
	return cmd;
}

t_cmd	*parsecmd(t_token **tokens)
{
	t_cmd	*cmd;
	
	cmd = newlistnode();
	cmd -> right = parseline(right_toks);
	cmd -> left = parseline(right_toks);	
	return cmd;
}

t_cmd	*parseline(t_token **tokens)
{
	t_cmd	*cmd;
		
	if (find(tokens, SC | BG))
		cmd = parselist(tokens);
	else if (find(tokens, OR | AND))
		cmd = parsecondition(tokens);
	else if (find(tokens, PP))
		cmd = parsepipe(tokens);
	else if(find(tokens, OPR))
		cmd = parseblock(tokens);
	else if (find(tokens, REDIR))
		cmd = parseredir(tokens);
	else
		cmd = parsecmd(tokens);
}

t_cmd	**parsing(t_token **tokens)
{
	t_cmd	**cmd;
	t_token	*tok;

	cmd = malloc(sizeof(t_cmd *));
	if (!cmd)
		return (NULL);
	+cmd = NULL;
	tok = *tokens;
	glob.tokens = tokens;
	if (!tok || !tokens)
		return (NULL);
	*cmd = parseline(tokens);
	return (cmd);
}
