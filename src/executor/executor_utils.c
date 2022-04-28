/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 20:25:54 by obeaj             #+#    #+#             */
/*   Updated: 2022/04/28 00:11:20 by obeaj            ###   ########.fr       */
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
		write(2, "minishell: ", 11);
		while (s[i])
		{
			write(1, &s[i], 1);
			i++;
		}
		write(2, ": Command not found\n", 20);
		return (1);
	}
	return (1);
}

char	*get_path(char *cmd)
{
	char	*path;
	char	p;
	int		i;
	char	**new_cmd;

	p = get_venv("PATH", g_glob.venv);
	new_cmd = NULL;
	i = 0;
	path = ft_strtok(p, ':');
	while (path)
	{
		path = ft_strdup(paths[i]);
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
