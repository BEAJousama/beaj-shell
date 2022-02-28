/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 09:51:36 by obeaj             #+#    #+#             */
/*   Updated: 2021/11/09 19:33:21 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*first;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		first = *lst;
		*lst = (*lst)-> next;
		del(first -> content);
		free(first);
	}
}
