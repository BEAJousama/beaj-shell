/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imabid <imabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:45:42 by obeaj             #+#    #+#             */
/*   Updated: 2022/03/12 18:07:19 by imabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
static int	check_n(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!str)
		return (1);
	if (str[j] == '-')
	{
		j++;
		while (str[j] == 'n' && str[j])
			j++;
		if (str[j] == '\0')
			i++;
	}
	return (i);
}
void    echo_cmd(char **cmd)
{
	int sign = 0;
    int i = 1;
   	int j = 0;
	while(cmd[i])
	{
		j = check_n(cmd[i]);
		if (j == 1)
			sign = 1;
		i++;
	}
	i = 1;
	while(cmd[i])
	{
		j = check_n(cmd[i]);
		if (j == 0)
		{
			while(cmd[i])
			{
				ft_putstr_fd(cmd[i++], 1);
				if(cmd[i] != '\0')
					ft_putchar_fd(' ', 1);
			}
			break ;
		}
		i++;
	}
	if (sign == 0)
		ft_putchar_fd('\n', 1);
}
