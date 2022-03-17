/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 14:02:51 by obeaj             #+#    #+#             */
/*   Updated: 2022/03/17 20:10:33 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_error(char *str, char *data)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(data, 2);
	ft_putchar_fd('\n', 2);
	return (1);
}

// char	*ft_strjoin(char *reste, char *buff)
// {
// 	char	*str;
// 	char	*pstr;
// 	char	*preste;

// 	if (!reste)
// 	{
// 		reste = (char *)malloc(1 * sizeof(char));
// 		*reste = '\0';
// 	}
// 	if (!buff)
// 		return (NULL);
// 	str = malloc(sizeof(char) * ((ft_strlen(reste) + ft_strlen(buff)) + 1));
// 	if (!str)
// 		return (NULL);
// 	pstr = str;
// 	preste = reste;
// 	if (preste)
// 		while (*preste)
// 			*str++ = *preste++;
// 	while (*buff)
// 		*str++ = *buff++;
// 	*str = '\0';
// 	free(reste);
// 	return (pstr);
// }