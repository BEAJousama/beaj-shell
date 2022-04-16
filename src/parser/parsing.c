/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 12:32:11 by obeaj             #+#    #+#             */
/*   Updated: 2022/04/14 01:33:14 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_glob glob;

// t_cmd	*newnode(t_tok tok)
// {
// 	t_cmd	*cmd;
	
// 	cmd = malloc(sizeof(t_cmd));
// 	if (!cmd)
// 		return (NULL);
// 	cmd -> type = AST_SC;
// 	return (cmd);
// }

t_cmd	*NewAstNode(t_tok tok)
{
	t_cmd	*cmd;
	
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	if ((tok & SC) & SC)
		cmd -> type = AST_SC;
	else if ((tok & BG) & BG)
		cmd -> type = AST_BG;
	else if (tok & PP)
		cmd -> type = AST_PIPE;
	else if ((tok & OR) & OR)
		cmd -> type = AST_OR;
	else if ((tok & AND) & AND)
		cmd -> type = AST_AND;
	else if (tok & OPR)
		cmd -> type = AST_SUB;
	return (cmd);
}

t_cmd	*NewRediNode(t_split sp)
{
	t_redircmd	*cmd;
	
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	if ((sp.tok & GTH) & GTH)
		cmd -> type = AST_GTH;
	else if ((sp.tok & GGTH) & GGTH)
		cmd -> type = AST_GGTH;
	else if ((sp.tok & LTH) & LTH)
		cmd -> type = AST_LTH;
	else if ((sp.tok & HDOC) & HDOC)
		cmd -> type = AST_HDOC;
	cmd -> file = (*sp.left) -> data;
	if (!(sp.right))
		cmd 
		
	return ((t_cmd **)cmd);
}

t_cmd	*parselist(t_token **tokens)
{
	t_cmd	*cmd;
	t_split sp;
	
	sp = find(tokens, SC | BG, 0);
	cmd = NewAstNode(sp.tok);
	if (!cmd)
		return (NULL);
	cmd -> right = parseline(sp.right);
	cmd -> left = parseline(sp.left);
	return (cmd);
}

t_cmd	*parsecondition(t_token **tokens)
{
	t_cmd	*cmd;
	t_split sp;
	
	sp = find(tokens, OR | AND, 0);
	cmd = NewAstNode(sp.tok);
	if (!cmd)
		return (NULL);
	cmd -> right = parseline(sp.right);
	cmd -> left = parseline(sp.left);	
	return (cmd);
}

t_cmd	*parsepipe(t_token **tokens)
{
	t_cmd	*cmd;
	t_split sp;
	
	sp = find(tokens, PP, 0);
	cmd = NewAstNode(sp.tok);
	if (!cmd)
		return (NULL);
	cmd -> right = parseline(sp.right);
	cmd -> left = parseline(sp.left);	
	return (cmd);
}

t_cmd	*parseblock(t_token **tokens)
{
	t_cmd	*cmd;
	t_split sp;
	
	sp = find(tokens, OPR, 1);
	cmd = NewAstNode(sp.tok);
	if (!cmd)
		return (NULL);
	cmd -> right = NULL;
	cmd -> left = parseline(sp.left);	
	return (cmd);
}

t_cmd	*parseredir(t_token **tokens)
{
	t_cmd	*cmd;
	t_split sp;
	
	sp = find(tokens, REDIR);
	cmd = NewRediNode(sp);
	if (!cmd)
		return (NULL);
	cmd -> right = parseline(sp.right);
	cmd -> left = parseline(sp.left);	
	return (cmd);
}

t_cmd	*parsecmd(t_token **tokens)
{
	t_cmd	*cmd;
	
	cmd = newlistnode();
	cmd -> right = parseline(right_toks);
	cmd -> left = parseline(right_toks);	
	return (cmd);
}

t_cmd	*parseline(t_token **tokens)
{
	t_cmd	*cmd;
		
	if (is_there(tokens, SC | BG, 0))
		cmd = parselist(tokens);
	else if (is_there(tokens, OR | AND, 0))
		cmd = parsecondition(tokens);
	else if (is_there(tokens, PP, 0))
		cmd = parsepipe(tokens);
	else if(is_there(tokens, OPR, 1))
		cmd = parseblock(tokens);
	else if (is_there(tokens, REDIR, 0))
		cmd = parseredir(tokens);
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
	*cmd = NULL;
	tok = *tokens;
	glob.tokens = tokens;
	if (!tok || !tokens)
		return (NULL);
	*cmd = parseline(tokens);
	return (cmd);
}
