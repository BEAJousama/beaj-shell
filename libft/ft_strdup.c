/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 08:59:07 by obeaj             #+#    #+#             */
/*   Updated: 2021/11/09 10:13:00 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*dest;
	int		i;

	i = 0;
	dest = (char *)malloc(ft_strlen(src) + 1);
	if (dest != NULL)
	{
		while (*(src + i))
		{
			*(dest + i) = *(src + i);
			i++;
		}
		*(dest + i) = '\0';
		return (dest);
	}
	return (NULL);
}
