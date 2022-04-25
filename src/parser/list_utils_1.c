/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 16:43:25 by obeaj             #+#    #+#             */
/*   Updated: 2022/04/25 01:28:04 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token **tokens)
{
	t_token	*first;

	first = *tokens;
	while (first)
	{
		if (first-> tok & WC && first -> group)
		{
			while (*first -> group != NULL)
			{
				if ((*first -> group)->data)
					free((*first -> group)->data);
				free(*first -> group);
				(*first -> group) = (*first -> group)->next;
			}
			free(first -> group);
		}
		if (first->data)
			free(first->data);
		free(first);
		first = first-> next;
	}
	free(tokens);
}
