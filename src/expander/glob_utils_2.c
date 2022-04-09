/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 14:54:49 by obeaj             #+#    #+#             */
/*   Updated: 2022/04/06 16:09:21 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_glob glob;

void	del_venv(char *key)
{
	t_venv	*venv;
	t_venv	*vnext;

	venv = *glob.venv;
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

	venv = glob.venv;
	var = glob.vars;
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
