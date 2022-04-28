/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imabid <imabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:45:50 by obeaj             #+#    #+#             */
/*   Updated: 2022/04/28 18:25:16 by imabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_go(t_m *m, int i)
{
	char	*key;
	char	*val;

	key = get_key(m->echo[i]);
	val = get_value(m->echo[i]);
	add_global_venv(key, val, glob.venv);
}

void	check_plusegal(char *arg, t_m *m)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (arg[++i])
	{
		if (arg[i] != '+' && arg[i + 1] != '=')
			m->key[j] = arg[i];
		j++;
	}
}

void	addto_key(char *arg)
{
	t_m	m;

	m.key = get_key(arg);
	m.val = get_value(arg);
	m.key = malloc(ft_strlen(m.key));
	check_plusegal(arg, &m);
	m.v = get_venv(m.key, glob.venv);
	if (m.v)
	{
		m.cokey = ft_strjoin(get_venv(m.key, glob.venv), m.val);
		add_global_venv(m.key, m.cokey, glob.ennv);
		add_global_venv(m.key, m.cokey, glob.venv);
	}
	else
	{
		add_global_venv(m.key, m.val, glob.ennv);
		add_global_venv(m.key, m.val, glob.venv);
	}
	free(m.key);
}

void	check_args(t_m *m)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (m->echo[i])
	{
		if (ft_isalpha(m->echo[i][0]) || m->echo[i][0] == '_')
		{
			if (if_egal(m->echo[i]) && !if_plusegal(m->echo[i]))
			{
				env_go(m->echo[i]);
				export_go(m, i);
				glob.g = 1;
			}
			if (if_plusegal(m->echo[i]))
				addto_key(m->echo[i]);
			if (!if_egal(m->echo[i]))
				export_go(m, i);
		}
		else
		{
			print_error("export: `", m->echo[i], "': not a valid identifier\n");
			glob.status = 1;
		}
		i++;
	}
}

void	export_cmd(t_m *m)
{
	if (!m->echo[1])
	{
		sort_env(glob.venv);
		glob.status = 0;
	}
	else
		check_args(m);
}
