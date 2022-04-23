/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imabid <imabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:46:14 by obeaj             #+#    #+#             */
/*   Updated: 2022/04/16 17:25:46 by imabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path(char **str)
{
	int		i;
	int		j;
	int		x;
	char	*to_find;

	to_find = "PATH";
	i = 0;
	while (str[i])
	{
		j = 0;
		x = 0;
		while (to_find[j] == str[i][x])
		{
			if (str[i][j + 1] == '=')
			{
				return (&str[i][x + 2]);
			}
			j++;
			x++;
		}
		i++;
	}
	return (0);
}

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

char	*get_path(char	**paths, char **cmd)
{
	char	*path;
	int		i;
	char **new_cmd;

	new_cmd = NULL;

	i = 0;
	while (paths[i])
	{
		path = ft_strdup(paths[i]);
		path = ft_strjoin(path, "/");
		path = ft_strjoin(path, cmd[0]);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	get_error(cmd[0]);
	return (0);
}
