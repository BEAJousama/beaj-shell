/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imabid <imabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:45:45 by obeaj             #+#    #+#             */
/*   Updated: 2022/04/20 17:47:47 by imabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_cmd(t_mini *mini)
{
	int	i;

	i = 1;
	if (mini->args[1])
		print_error("env: ", mini->args[1], ": No such file or directory\n");
	else
		show_vars();
}
