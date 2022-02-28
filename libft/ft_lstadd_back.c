/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 08:41:46 by obeaj             #+#    #+#             */
/*   Updated: 2021/11/09 19:03:22 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*first;

	if (!lst)
		return ;
	if (*lst)
	{
		first = *lst;
		while (first -> next)
			first = first -> next;
		first -> next = new;
	}
	else
		*lst = new;
}
