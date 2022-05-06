/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:26:41 by obeaj             #+#    #+#             */
/*   Updated: 2022/05/06 00:11:15 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_glob	g_glob = {.venv = NULL, .ennv = NULL, .vars = NULL, .buff = NULL,
	.status = 0, .hdoc = 0, .io = {0}, .cmd = NULL, .fd = {0}};

t_venv	**set_global_env(char **env, t_venv **ennv)
{
	int		len;
	t_venv	*new;

	ennv = init_venv(ennv);
	len = 0;
	while (*(env + len))
	{
		new = new_venv(get_key(*(env + len)), get_value(*(env + len)));
		venv_add_back(ennv, new);
		len++;
	}
	return (ennv);
}

t_venv	**set_global_vars(t_venv **vars)
{
	vars = init_venv(vars);
	add_global_venv("?", ft_itoa(g_glob.status), vars);
	add_global_venv("$", ft_itoa(g_glob.status), vars);
	add_global_venv("0", "minishell", vars);
	return (vars);
}

void	add_global_venv(char *key, char *value, t_venv **all)
{
	int		len;
	t_venv	*venv;
	char	*tmp;

	len = 0;
	tmp = get_venv(key, all);
	if (!tmp)
	{
		venv = new_venv(key, value);
		venv_add_back(all, venv);
	}
	else if ((ft_strcmp(tmp, value)))
	{
		venv = *all;
		while (venv)
		{
			if (!ft_strcmp(key, venv -> key))
				venv -> value = value;
			venv = venv -> next;
		}		
	}
}

char	*get_venv(char *key, t_venv **all)
{
	t_venv	*venv;

	venv = *all;
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
