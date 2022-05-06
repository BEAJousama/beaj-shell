/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:33:18 by obeaj             #+#    #+#             */
/*   Updated: 2022/05/06 15:40:37 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	venv_count(t_venv *venv)
{
	int	counter;

	counter = 0;
	while (venv)
	{
		counter++;
		venv = venv->next;
	}
	return (counter);
}

char	**venv_export_array(t_venv	*venv)
{
	t_m	m;

	m.i = 0;
	m.len = venv_count(venv);
	m.env = malloc(sizeof(char *) * (m.len + 1));
	while (venv && m.i < m.len)
	{
		m.path = ft_strjoin(venv->key, "=");
		m.val = m.path;
		m.path = ft_strjoin(m.path, venv->value);
		free(m.val);
		m.env[m.len - m.i++ - 1] = m.path;
		venv = venv->next;
	}
	m.env[m.len] = NULL;
	return (m.env);
}

int	ft_execve(char **cmd)
{
	char	*path;
	char	**env;
	int		pid;
	int		status;

	env = venv_export_array(*g_glob.venv);
	path = get_path(*cmd);
	if (!path)
		return (127);
	pid = fork();
	if (pid == -1)
		return (-2);
	else if (pid == 0)
	{
		if (execve(path, cmd, env) == -1)
			exit (127);
		if (errno == ENOENT)
			exit(127);
		if (errno == EACCES)
			exit(126);
	}
	waitpid(pid, &status, WUNTRACED);
	g_glob.status = get_status(status);
	free(path);
	free_tab(env);
	return (g_glob.status);
}
