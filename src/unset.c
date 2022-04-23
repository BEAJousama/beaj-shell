/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imabid <imabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:45:56 by obeaj             #+#    #+#             */
/*   Updated: 2022/04/20 18:03:29 by imabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unvalid_arg(char *arg)
{
	int	i;

	if (!arg)
		return (0);
	i = 0;
	if (ft_isalpha(arg[i]) || arg[i] == '_')
	{
		while (arg[++i])
			if (!(ft_isalnum(arg[i]) || arg[i] == '_'))
				return (0);
		return (1);
	}
	return (0);
}

void	unset_cmd(t_mini *mini)
{
	int	i;
	int	ind;

	ind = 0;
	i = 0;
	while (mini->args[++i])
	{
		if (!unvalid_arg(mini->args[i]))
		{
			ind = -1;
			break ;
		}
		del_venv(mini->args[i]);
		del_ennv(mini->args[i]);
	}
	if (ind == -1)
		print_error("unset: `", mini->args[i], "': not a valid identifier\n");
}
