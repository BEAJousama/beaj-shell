/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:46:14 by obeaj             #+#    #+#             */
/*   Updated: 2022/04/25 15:33:41 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// typedef struct s_vars
// {
// 	char	**cmd1;
// 	char	*path1;
// 	char	**cmd2;
// 	char	*path2;
// 	char	**env;
// 	int		f1;
// 	int		f2;
// }	t_vars;

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

char	*get_path(char	**paths, char	**cmd)
{
	char	*path;
	int		i;
	int		j;

	j = 0;
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

// int main(int ac,char **av,char **env)
// {
//     char **paths;
//     char	**cmd1;
//     char	*path1;
//     paths = ft_split(find_path(env), ':');
//     cmd1 = ft_split(av[1], ' ');
// 	path1 = get_path(paths, cmd1);
//     execve(path1,cmd1,env);
// }
// void    executor(char *path, char **cmd, char **env)
// {
//     execve(path, cmd, env);
// }