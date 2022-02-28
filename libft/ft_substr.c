/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 10:59:09 by obeaj             #+#    #+#             */
/*   Updated: 2021/11/03 15:12:49 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	char			*t;
	size_t			lenght;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	lenght = ft_strlen(s + start);
	if (lenght >= len)
		lenght = len;
	sub = (char *)malloc(lenght + 1);
	t = sub;
	if (!sub)
		return (NULL);
	while (*(s + start) && lenght-- > 0)
	{
		*sub = *(s + start);
		s++;
		sub++;
	}
	*sub = '\0';
	return (t);
}
