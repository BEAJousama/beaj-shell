/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imabid <imabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:39:07 by imabid            #+#    #+#             */
/*   Updated: 2022/03/24 18:39:24 by imabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	a;
	unsigned char	b;

	i = 0;
	while ((s1[i] || s2[i]))
	{
		a = s1[i];
		b = s2[i];
		if (a && b == '\0')
			return (a);
		if (a == '\0' && b)
			return (-b);
		if (a != b)
			return (a - b);
		i++;
	}
	return (0);
}