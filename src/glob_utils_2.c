/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imabid <imabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 14:54:49 by obeaj             #+#    #+#             */
/*   Updated: 2022/04/20 17:50:09 by imabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_glob glob;

void	del_venv(char *key)
{
	t_venv	*venv;
	t_venv	*vnext;

	venv = *glob.venv;
	if (!ft_strcmp(key, venv -> key))
	{
		*glob.venv = (*glob.venv)-> next;
		free (venv);
	}
	else
	{
		while (venv -> next)
		{
			vnext = venv -> next;
			if (!ft_strcmp(key, vnext -> key))
				break ;
			venv = venv -> next;
		}
		venv -> next = vnext -> next;
		// if (venv)
		// 	free(venv);
	}
}
void	del_ennv(char *key)
{
	t_venv	*venv;
	t_venv	*vnext;

	venv = *glob.ennv;
	if (!ft_strcmp(key, venv -> key))
	{
		*glob.ennv = (*glob.ennv)-> next;
		free (venv);
	}
	else
	{
		while (venv -> next)
		{
			vnext = venv -> next;
			if (!ft_strcmp(key, vnext -> key))
				break ;
			venv = venv -> next;
		}
		venv -> next = vnext -> next;
		// if (venv)
		// 	free(venv);
	}
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
