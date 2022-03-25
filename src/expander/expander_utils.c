/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 17:28:10 by obeaj             #+#    #+#             */
/*   Updated: 2022/03/19 12:41:06 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
static size_t	ft_strlen1(const	char *s)
{
	size_t	len;

	len = 0;
	while (*s++)
		len++;
	return (len);
}
char	*ft_strjoin1(char *s1, char *s2)
{
	int		len_tot;
	char	*s;

	if (!s2 || !s1)
		return (NULL);
	len_tot = ft_strlen1(s1) + ft_strlen1(s2) + 2;
	s = (char *)malloc(len_tot * sizeof(char));
	if (!s)
		return (NULL);
	while (*s1)
		*s++ = *s1++;
	*s++ = ' ';
	while (*s2)
		*s++ = *s2++;
	*s = '\0';
	return (s - len_tot + 1);
}
