/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imabid <imabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:45:42 by obeaj             #+#    #+#             */
/*   Updated: 2022/03/11 20:21:01 by imabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    echo_cmd(char **cmd)
{
    int i;
    int j;
    if(!ft_strncmp(cmd[0], "echo",4) && !ft_strncmp(cmd[1], "-n",2))
	{
			i = 1;
			j = 1;
			while(cmd[i])
			{
				if(!ft_strncmp(cmd[i],"-n",2))
					j++;
				if(ft_strncmp(cmd[i],"-n",2))
					break;
				if()
				i++;
			}
        while(cmd[j])
        {
            if(cmd[j + 1] != '\0')
                printf("%s ",cmd[j]);
            if(cmd[j + 1] == '\0')
                printf("%s",cmd[j]);
            j++;
        }
	}
	else
	{
		i = 0;
		while(cmd[++i])
		{
			if(cmd[i + 1] != '\0')
    		printf("%s ",cmd[i]);
    		if(cmd[i + 1] == '\0')
    		 printf("%s",cmd[i]);
		}
		printf("\n");
	}
    // j++;
    // while(cmd[j])
    // {
    //     if(cmd[j + 1] != '\0')
    //         printf("%s ",cmd[j]);
    //     if(cmd[j + 1] == '\0')
    //         printf("%s",cmd[j]);
            
    //     j++;
    // }
}