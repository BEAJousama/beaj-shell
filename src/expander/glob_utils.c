/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:26:41 by obeaj             #+#    #+#             */
/*   Updated: 2022/04/21 02:09:32 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_glob	g_glob = {.venv = NULL, .vars = NULL, .status = 0, .tokens = NULL};

void	set_global_env(char **env)
{
	int		len;
	t_venv	*new;

	g_glob.venv = init_venv(g_glob.venv);
	g_glob.vars = init_venv(g_glob.vars);
	len = 0;
	while (*(env + len))
	{
		new = new_venv(get_key(*(env + len)), get_value(*(env + len)));
		venv_add_back(g_glob.venv, new);
		len++;
	}
}

void	add_global_vars(char *key, char *value)
{
	int		len;
	t_venv	*var;

	len = 0;
	var = new_venv(key, value);
	venv_add_back(g_glob.vars, var);
}

void	add_global_venv(char *key, char *value)
{
	int		len;
	t_venv	*venv;
	char	*tmp;

	len = 0;
	tmp = get_venv(key);
	if (!tmp)
	{
		venv = new_venv(key, value);
		venv_add_back(g_glob.venv, venv);
	}
	else if ((*tmp && ft_strcmp(tmp, value)))
	{
		venv = *g_glob.venv;
		while (venv)
		{
			if (!ft_strcmp(key, venv -> key))
				venv -> value = value;
			venv = venv -> next;
		}		
	}
}

char	*get_venv(char *key)
{
	t_venv	*venv;

	venv = *g_glob.venv;
	while (venv)
	{
		if (!ft_strcmp(venv -> key, key))
			return (venv -> value);
		venv = venv -> next;
	}
	return (NULL);
}

char	*get_var(char *key)
{
	t_venv	*var;

	var = *g_glob.vars;
	while (var)
	{
		if (!ft_strcmp(var -> key, key))
			return (var -> value);
		var = var -> next;
	}
	return (NULL);
}
