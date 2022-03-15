/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyzer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 18:59:44 by obeaj             #+#    #+#             */
/*   Updated: 2022/03/14 15:20:37 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void analyzer(t_token **tokens)
{
	t_token	*first;
	t_token	*right;
	t_token	*left;

	first = *tokens;
	while (first)
	{
		right = first -> next;
		left = first -> prev; 
		if (!ft_strncmp(first->type , "OPAR", 4))
		{
			if (ft_strncmp(right->type , "OPAR", 4) && ft_strncmp(right->type , "WORD", 4)
				&& ft_strncmp(right->type , "GTHAN", 5) && ft_strncmp(right->type , "GGTHAN", 6)
				&& ft_strncmp(right->type , "LTHAN", 5) && ft_strncmp(right->type , "HDOC", 4))
			{
				perror("SYntax Error");
			}
			if (ft_strncmp(left->type , "AND", 3) && ft_strncmp(left->type , "OR", 2)
				&& ft_strncmp(left->type , "PIPE", 4) && ft_strncmp(left->type , "OPAR", 4))
			{
				perror("SYntax Error");
			}
		}
		else if(!ft_strncmp(first->type , "CPAR", 4))
		{
			if (ft_strncmp(right->type , "CPAR", 4) && ft_strncmp(right->type , "WORD", 4))
			{
				perror("SYntax Error");
			}
			if (ft_strncmp(left->type , "AND", 3) && ft_strncmp(left->type , "OR", 2)
				&& ft_strncmp(left->type , "PIPE", 4) && ft_strncmp(left->type , "CPAR", 4)
				&& ft_strncmp(left->type , "SEMIC", 5))
			{
				perror("SYntax Error");
			}
		}
		else if(!ft_strncmp(first->type , "GTHAN", 5) || !ft_strncmp(first->type , "GGTHAN", 6)
				|| !ft_strncmp(first->type , "LTHAN", 5) || !ft_strncmp(first->type , "HDOC", 4))
		{
			if (ft_strncmp(right->type , "WORD", 4))
			{
				perror("SYntax Error");
			}
		}
		else if(!ft_strncmp(first->type , "AND", 3) || !ft_strncmp(first->type , "OR", 2)
				|| !ft_strncmp(first->type , "PIPE", 4))
		{
			if (ft_strncmp(right->type , "CPAR", 4) && ft_strncmp(right->type , "WORD", 4))
			{
				perror("SYntax Error");
			}
			if (ft_strncmp(right->type , "OPAR", 4) && ft_strncmp(right->type , "WORD", 4)
				&& ft_strncmp(right->type , "GTHAN", 5) && ft_strncmp(right->type , "GGTHAN", 6)
				&& ft_strncmp(right->type , "LTHAN", 5) && ft_strncmp(right->type , "HDOC", 4))
			{
				perror("SYntax Error");
			}
		}
		first = first -> next;
	}
}