/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 20:25:54 by obeaj             #+#    #+#             */
/*   Updated: 2022/05/05 00:33:39 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_error(char *s)
{
	int	i;

	i = 0;
	if (!s)
	{
		write(2, "invalid command!\n", 18);
		return (1);
	}
	else
	{
		print_error_("minishell: ", s, ": Command not found\n");
		return (1);
	}
	return (1);
}

char	*get_path(char *cmd)
{
	char	*path;
	char	*p;
	int		i;

	if (!cmd)
		cmd = ft_strdup("");
	p = get_venv("PATH", g_glob.venv);
	i = 0;
	if (access(cmd, X_OK) == 0)
		return (cmd);
	path = ft_strtok(p, ':');
	while (path)
	{
		path = ft_strjoin(path, "/");
		path = ft_strjoin(path, cmd);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		path = ft_strtok(NULL, ':');
		i++;
	}
	get_error(cmd);
	return (0);
}

int	get_status(int status)
{
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	else if (WIFSTOPPED(status))
		return (128 + WSTOPSIG(status));
	else if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

pid_t	ft_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (print_error("fork", strerror(errno)), -1);
	return (pid);
}
