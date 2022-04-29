/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imabid <imabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:45:45 by obeaj             #+#    #+#             */
/*   Updated: 2022/04/29 15:10:37 by imabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_go(char *arg)
{
	char	*key;
	char	*val;

	key = get_key(arg);
	val = get_value(arg);
	add_global_venv(key, val, glob.ennv);
}

void	env_cmd(char **args)
{
	int	i;

	i = 1;
	if (args[1])
	{
		print_error("env: ", args[1], ": No such file or directory\n");
		glob.status = 127;
	}
	else
	{
		show_vars();
		glob.status = 0;
	}
}
