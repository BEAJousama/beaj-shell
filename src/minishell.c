/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 10:28:27 by obeaj             #+#    #+#             */
/*   Updated: 2022/05/07 01:06:39 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shlvl_add(t_m *m)
{
	m->shlvl = ft_atoi(get_venv("SHLVL", g_glob.venv));
	m->shlvl++;
	add_global_venv(ft_strdup("SHLVL"), ft_itoa(m->shlvl), g_glob.venv);
	add_global_venv(ft_strdup("SHLVL"), ft_itoa(m->shlvl), g_glob.ennv);
}

void	lets_start(char **env)
{
	g_glob.venv = set_global_env(env, g_glob.venv);
	g_glob.ennv = set_global_env(env, g_glob.ennv);
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_cmd	**cmd;
	t_token	**toks;
	t_m		m;

	(void)av;
	if (ac > 1)
		return (0);
	g_glob.gc = init_gc();
	lets_start(env);
	shlvl_add(&m);
	save_io(g_glob.io);
	line = readline("minishell-> ");
	while (line)
	{
		toks = lexer(&line, env);
		if (!toks)
		{
			line = readline("minishell-> ");
			continue ;
		}
		cmd = parsing(toks);
		if (runcmd(*cmd) || !cmd)
		{
			line = readline("minishell-> ");
			continue ;
		}
		line = readline("minishell-> ");
		reset_io(g_glob.io);
	}
	return (0);
}
