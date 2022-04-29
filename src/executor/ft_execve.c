/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:33:18 by obeaj             #+#    #+#             */
/*   Updated: 2022/04/29 20:41:17 by obeaj            ###   ########.fr       */
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
	int		i;
	int		len;
	char	*str;
	char	**env;

	i = 0;
	len = venv_count(venv);
	env = malloc(sizeof(char *) * (len + 1));
	while (venv && i < len)
	{	
		str = ft_strjoin(venv->key, "=");
		str = ft_strjoin(str, venv->value);
		env[len - i++ - 1] = str;
		venv = venv->next;
	}
	env[len] = NULL;
	return (env);
}

int	ft_execve(char **cmd)
{
	char	*path;
	char	**env;
	int		pid;

	env = venv_export_array(*g_glob.venv);
	path = get_path(*cmd);
	pid = fork();
	if (pid == -1)
		return (-2);
	else if (pid == 0)
	{
		if (execve(path, cmd, env) == -1)
			return (-1);
	}
	wait(&g_glob.status);
	return (0);
}
