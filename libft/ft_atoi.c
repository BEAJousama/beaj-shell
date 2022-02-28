/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 16:23:32 by obeaj             #+#    #+#             */
/*   Updated: 2021/11/06 13:47:18 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	s;
	int	result;

	result = 0;
	s = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-')
		s *= -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && str[i] <= '9' && str[i] >= '0')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	result *= s;
	return (result);
}
