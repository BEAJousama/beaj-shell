/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imabid <imabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:46:14 by obeaj             #+#    #+#             */
/*   Updated: 2022/04/28 18:27:13 by imabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*find_path(char **str)
// {
// 	int		i;
// 	int		j;
// 	int		x;
// 	char	*to_find;

// 	to_find = "PATH";
// 	i = 0;
// 	while (str[i])
// 	{
// 		j = 0;
// 		x = 0;
// 		while (to_find[j] == str[i][x])
// 		{
// 			if (str[i][j + 1] == '=')
// 			{
// 				return (&str[i][x + 2]);
// 			}
// 			j++;
// 			x++;
// 		}
// 		i++;
// 	}
// 	return (0);
// }

// int	get_error(char *s)
// {
// 	int	i;

// 	i = 0;
// 	if (!s)
// 	{
// 		write(2, "invalid command!\n", 18);
// 		return (1);
// 	}
// 	else
// 	{
// 		write(2, "minishell: ", 11);
// 		while (s[i])
// 		{
// 			write(1, &s[i], 1);
// 			i++;
// 		}
// 		write(2, ": Command not found\n", 20);
// 		glob.status = 127;
// 		return (1);
// 	}
// 	return (1);
// }

// char	*get_path(char	**paths, char **cmd)
// {
// 	char	*path;
// 	int		i;
// 	char **new_cmd;

// 	new_cmd = NULL;

// 	i = 0;
// 	while (paths[i])
// 	{
// 		path = ft_strdup(paths[i]);
// 		path = ft_strjoin(path, "/");
// 		path = ft_strjoin(path, cmd[0]);
// 		if (access(path, X_OK) == 0)
// 			return (path);
// 		free(path);
// 		i++;
// 	}
// 	get_error(cmd[0]);
// 	return (0);
// }

char    *ft_strtok(char *str, char sepa)
{
    static char    *stock = NULL;
    char        *ptr;
    int            i;

    i = 0;
    ptr = NULL;
    if (str != NULL)
        stock = ft_strdup(str);
    while (*stock != '\0')
    {
        if (i == 0 && *stock != sepa)
        {
            i = 1;
            ptr = stock;
        }
        else if (i == 1 && *stock == sepa)
        {
            *stock = '\0';
            stock += 1;
            break ;
        }
        stock++;
    }
    return (ptr);
}

int    get_error(char *s)
{
    int    i;

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
		glob.status = 127;
        return (1);
    }
    return (1);
}

char    *get_path(char *cmd)
{
    char    *path;
    char    *p;
    int        i;
    char    **new_cmd;

    p = get_venv("PATH", glob.venv);
    new_cmd = NULL;
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
