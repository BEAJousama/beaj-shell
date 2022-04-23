/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imabid <imabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:25:01 by imabid            #+#    #+#             */
/*   Updated: 2022/04/12 18:25:03 by imabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *s, int len)
{
	char	*copy;

	copy = (char *)malloc(len * sizeof(char));
	if (!copy)
		return (NULL);
	ft_strlcpy(copy, s, len);
	return (copy);
}