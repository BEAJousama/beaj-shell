/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 16:43:25 by obeaj             #+#    #+#             */
/*   Updated: 2022/04/21 16:46:43 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token **tokens)
{
	t_token	*first;

	first = NULL;
	while (*tokens)
	{
		first = (*tokens)-> next;
		if ((*tokens)-> group)
			free_group((*tokens)-> group);
		free((*tokens)->data);
		free(*tokens);
		(*tokens) = first;
	}
	free(tokens);
}