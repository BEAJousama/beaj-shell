/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 14:54:49 by obeaj             #+#    #+#             */
/*   Updated: 2022/04/27 04:23:25 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_venv(char *key)
{
	t_venv	*venv;
	t_venv	*vnext;

	venv = *g_glob.venv;
	if (!ft_strcmp(key, venv -> key))
	{
		*g_glob.venv = (*g_glob.venv)-> next;
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
	}
}

char	*get_venv_all(char *key)
{
	char	*value;

	value = get_venv(key, g_glob.vars);
	if (!value)
		value = get_venv(key, g_glob.venv);
	if (!value)
		value = get_venv(key, g_glob.ennv);
	if (!value)
		return (NULL);
	return (value);
}

void	del_ennv(char *key)
{
	t_venv	*venv;
	t_venv	*vnext;

	venv = *g_glob.ennv;
	if (!ft_strcmp(key, venv -> key))
	{
		*g_glob.ennv = (*g_glob.ennv)-> next;
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
	}
}

void	free_glob(void)
{
	t_venv	**venv;
	t_venv	**var;

	venv = g_glob.venv;
	var = g_glob.vars;
	while (*venv)
	{
		free((*venv)-> key);
		free((*venv)-> value);
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
