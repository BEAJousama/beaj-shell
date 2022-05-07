/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 10:28:27 by obeaj             #+#    #+#             */
/*   Updated: 2022/05/07 20:47:50 by obeaj            ###   ########.fr       */
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

int    ft_putchar(int c)
{
    write(1, &c, 1);
    return (1);
}

void	ctrl_d(void)
{
	char	*sr_cap;

	sr_cap = tgetstr("sr", NULL);
	tputs(sr_cap, 0, ft_putchar);
	ft_putstr_fd("minishell$ exit\n",1);
	exit(0);
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
	while (1)
	{
		line = readline("minishell-> ");
		gc_add_back(new_gcnode((void *)line));
		if (!line)
			ctrl_d();
		toks = lexer(&line, env);
		if (toks)
		{
			cmd = parsing(toks);
			runcmd(*cmd);
		}
		reset_io(g_glob.io);
	}
	return (0);
}
