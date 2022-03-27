/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imabid <imabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:45:45 by obeaj             #+#    #+#             */
/*   Updated: 2022/03/27 15:12:42 by imabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    env_cmd(t_mini *mini)
{
    int i;

    i = 0;
    if(mini->args[1])
    {
        ft_putstr_fd("env: ", 2);
		ft_putstr_fd(mini->args[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
    }
	else
	{
    	while (mini->env_g[i])
		{
			if (ft_strchr(mini->env_g[i], '='))
			{
				ft_putstr_fd(mini->env_g[i], 1);
				ft_putchar_fd('\n', 1);
			}
			i++;
		}
	}
}