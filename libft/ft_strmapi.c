/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 12:59:48 by obeaj             #+#    #+#             */
/*   Updated: 2021/11/08 13:41:40 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	unsigned int	length;
	char			*t;

	i = 0;
	if (!s || !f)
		return (NULL);
	length = ft_strlen(s);
	t = (char *)malloc(length + 1);
	if (!t)
		return (NULL);
	while (i < length)
	{
		*(t + i) = f(i, *(s + i));
		i++;
	}
	*(t + i) = '\0';
	return (t);
}
