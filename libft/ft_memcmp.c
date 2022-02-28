/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 11:00:07 by obeaj             #+#    #+#             */
/*   Updated: 2021/11/08 12:54:20 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char		*s11;
	const unsigned char	*s22;

	s11 = (unsigned char *)s1;
	s22 = (unsigned char *)s2;
	while (0 < n--)
	{
		if (*s11 != *s22)
			return (*s11 - *s22);
		s11++;
		s22++;
	}
	return (0);
}
