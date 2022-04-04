/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyzer_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 17:36:00 by obeaj             #+#    #+#             */
/*   Updated: 2022/04/04 18:28:46 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_par_match(t_token **tokens)
{
	t_token	*first;
	int		pcount;

	first = *tokens;
	pcount = 0;
	while (first)
	{
		if (first->tok == OPR)
			pcount++;
		if (first->tok == CPR)
			pcount--;
		first = first -> next;
	}
	if (pcount)
		return (print_error(UNCLOSED_PAR, "\n"));
	return (0);
}

int	check_quotes_match(t_token **tokens)
{
	t_token	*first;
	int		count[2];

	first = *tokens;
	count[0] = 0;
	count[1] = 0;
	while (first -> next)
	{
		if (first->tok == DQT)
			count[1] += 1;
		if (first->tok == QT)
			count[0] += 1;
		first = first -> next;
	}
	first = *tokens;
	while (first && (first -> tok != DQT) && (first -> tok != QT))
		first = first -> next;
	if (count[1] % 2 && first -> tok == DQT)
		return (print_error(UNCLOSED_DQ, "\0"));
	else if (count[0] % 2 && first -> tok == QT)
		return (print_error(UNCLOSED_SQ, "\0"));
	else if (count[1] % 2)
		return (print_error(UNCLOSED_DQ, "\0"));
	else if (count[0] % 2)
		return (print_error(UNCLOSED_SQ, "\0"));
	return (0);
}

int	check_parethesis(t_token **tokens)
{
	t_token	*first;
	t_token	*right;
	t_token	*left;

	first = *tokens;
	while (first -> next -> next)
	{
		right = first -> next;
		left = first -> prev;
		if (first -> tok == CPR)
		{
			if (!(left -> tok & (WORD | CPR)))
				return (print_error(UNEXPECTED_TOK, left -> data));
			else if (!(right -> tok & (CPR | BIND | BFG | CMDEND)))
				return (print_error(UNEXPECTED_TOK, right -> data));
		}
		if (first -> tok == OPR)
		{
			if (!(left -> tok & (OPR | CMDBEG | BIND | BFG)))
				return (print_error(UNEXPECTED_TOK, "("));
			else if (!(right -> tok & (WORD | REDIR | OPR)))
				return (print_error(UNEXPECTED_TOK, right -> data));
		}
		first = first -> next;
	}
	return (0);
}

int	check_binders(t_token **tokens)
{
	t_token	*first;
	t_token	*right;
	t_token	*left;

	first = *tokens;
	while (first -> next -> next)
	{
		right = first -> next;
		left = first -> prev;
		if (first -> tok & BIND)
		{
			if (!(left -> tok & (WORD | CPR)))
				return (print_error(UNEXPECTED_TOK, left -> data));
			else if (!(right -> tok & (WORD | REDIR | OPR)))
				return (print_error(UNEXPECTED_TOK, right -> data));
		}
		if (first -> tok & BFG)
		{
			if (!(left -> tok & (WORD | CPR)))
				return (print_error(UNEXPECTED_TOK, left -> data));
			else if (!(right -> tok & (WORD | REDIR | OPR | CMDEND)))
				return (print_error(UNEXPECTED_TOK, right -> data));
		}
		first = first -> next;
	}
	return (0);
}

int	check_redirect(t_token **tokens)
{
	t_token	*first;
	t_token	*right;

	first = *tokens;
	while (first -> next)
	{
		right = first -> next;
		if ((first -> tok & REDIR))
		{
			if (right -> tok & CMDEND)
				return (print_error(UNEXPECTED_TOK, "newline"));
			if (!(right -> tok & WORD))
				return (print_error(UNEXPECTED_TOK, right -> data));
		}
		first = first -> next;
	}
	return (0);
}
