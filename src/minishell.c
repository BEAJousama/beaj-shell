/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 10:28:27 by obeaj             #+#    #+#             */
/*   Updated: 2022/04/30 16:59:05 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shlvl_add(t_m *m)
{
	char	*val;

	m->shlvl = ft_atoi(get_venv("SHLVL",g_glob.venv));
	m->shlvl++;
	val = ft_itoa(m->shlvl);
	add_global_venv("SHLVL", val, g_glob.venv);
	add_global_venv("SHLVL", val, g_glob.ennv);
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
	lets_start(env);
	shlvl_add(&m);
	line = readline("minishell->");
	while (line)
	{
		if (*line)
			add_history(line);
		toks = lexer(&line, env);
		if (!toks)
		{
			line = readline("minishell->");
			continue ;
		}
		cmd = parsing(toks);
		if (runcmd(*cmd) || !cmd)
		{
			line = readline("minishell->");
			continue ;
		}
		line = readline("minishell->");
	}
	return (0);
}
