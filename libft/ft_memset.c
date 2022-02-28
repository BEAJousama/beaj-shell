/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 09:06:09 by obeaj             #+#    #+#             */
/*   Updated: 2021/11/08 13:23:21 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t len)
{
	unsigned char	*a;

	a = (unsigned char *)s;
	while (0 < len--)
	{
		*a = (unsigned char) c;
		a++;
	}
	return (s);
}
