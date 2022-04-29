/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:45:45 by obeaj             #+#    #+#             */
/*   Updated: 2022/04/29 15:55:41 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_go(char *arg)
{
	char	*key;
	char	*val;

	key = get_key(arg);
	val = get_value(arg);
	add_global_venv(key, val, g_glob.ennv);
}

void	env_cmd(char **args)
{
	int	i;

	i = 1;
	if (args[1])
	{
		print_error_("env: ", args[1], ": No such file or directory\n");
		g_glob.status = 127;
	}
	else
	{
		show_vars();
		g_glob.status = 0;
	}
}
