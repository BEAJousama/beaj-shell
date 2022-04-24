/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imabid <imabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:45:56 by obeaj             #+#    #+#             */
/*   Updated: 2022/04/24 16:20:15 by imabid           ###   ########.fr       */
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

void	unset_cmd(t_m *m)
{
	int	i;
	int	ind;

	ind = 0;
	i = 0;
	while (m->args[++i])
	{
		if (!unvalid_arg(m->args[i]))
		{
			ind = -1;
			break ;
		}
		del_venv(m->args[i]);
		del_ennv(m->args[i]);
	}
	if (ind == -1)
		print_error("unset: `", m->args[i], "': not a valid identifier\n");
}
