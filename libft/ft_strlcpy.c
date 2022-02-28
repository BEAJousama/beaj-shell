/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:44:57 by obeaj             #+#    #+#             */
/*   Updated: 2021/11/08 13:34:55 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	len;

	len = ft_strlen(src);
	if (dstsize > 0)
	{
		while (*src && dstsize - 1 > 0)
		{
			*dst++ = *src++;
			dstsize--;
		}
		*dst = '\0';
	}
	return (len);
}
