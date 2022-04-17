/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 12:32:11 by obeaj             #+#    #+#             */
/*   Updated: 2022/04/17 00:24:45 by obeaj            ###   ########.fr       */
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

t_cmd	*NewExecNode(t_tok tok)
{
	t_execcmd	*cmd;
	
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd -> type = AST_EXEC;
	return ((t_cmd *)cmd);
}

t_cmd	*NewRediNode(t_tok tok)
{
	t_redircmd	*cmd;
	
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	if (tok & GTH)
		cmd -> type = AST_GTH;
	else if ((tok & GGTH) & GGTH)
		cmd -> type = AST_GGTH;
	else if (tok & LTH)
		cmd -> type = AST_LTH;
	else if (tok  & HDOC)
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

t_tok	redir_tok(t_token *token)
{
	t_tok	tok;
	
	if ((token -> tok & GTH) & GTH)
		tok = GTH;
	else if (t(oken ->tok & GGTH) & GGTH)
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
	
	if ((*tokens)-> tok & REDIR)
	{
		token = redir_tok(t_token *tok);
		cmd = NewRediNode(token);	
		if (!cmd)
			return (NULL);
		
	}
	return (cmd);
}

t_cmd	*parsecmd(t_token **tokens)
{
	t_execcmd	*cmd;
	t_token	*first;
	int		ac;
	
	ac = 0;
	first = *tokens;
	cmd = NewExecNode(tokens);
	cmd = parseredir(cmd, tokens);
	while (first -> tok != CMDEND)
	{
		if (first -> tok & WC && first -> group)
		{
			while ((*first -> group))
			{
				cmd -> argv[ac] = ft_strdup((*first -> group) -> data);
				ac++;
				(*first -> group) = (*first -> group) -> next;
			}
		}
		else if (first & WORD)
			cmd -> argv[ac] = ft_strdup(first -> data);
		cmd = parseredir(cmd, tokens);
	}
	return ((t_cmd *)cmd);
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
