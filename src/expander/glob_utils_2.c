/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 14:54:49 by obeaj             #+#    #+#             */
/*   Updated: 2022/04/21 01:57:16 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_glob	g_glob;

void	del_venv(char *key)
{
	t_venv	*venv;
	t_venv	*vnext;

	venv = *g_glob.venv;
	while (venv -> next)
	{
		vnext = venv -> next;
		if (!ft_strcmp(key, vnext -> key))
			break ;
		venv = venv -> next;
	}
	venv -> next = vnext -> next;
	free(vnext);
}

void	free_glob(void)
{
	t_venv	**venv;
	t_venv	**var;

	venv = g_glob.venv;
	var = g_glob.vars;
	while (*venv)
	{
		free(*venv);
		*venv = (*venv)-> next;
	}
	while (*var)
	{
		free((*var)-> key);
		free((*var)-> value);
		free(*var);
		*var = (*var)-> next;
	}
	free(var);
	free(venv);
}
