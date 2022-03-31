/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 10:28:27 by obeaj             #+#    #+#             */
/*   Updated: 2022/03/31 13:27:10 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	*glob;

void	set_global_env(char **env)
{
	int		len;

	len = 0;
	while (*env[len])
		len++;
	glob->env = malloc(sizeof(char *) * len);
	len = 0;
	while (*env[len])
	{
		glob->env[len] = ft_strdup(env[len]);
		len++;
	}
}

void	set_global_vars(char **env)
{
	int		len;

	len = 0;
	while (*env[len])
		len++;
	glob->env = malloc(sizeof(char *) * len);
	len = 0;
	while (*env[len])
	{
		glob->env[len] = ft_strdup(env[len]);
		len++;
	}
}

char	*get_env(char *str)
{
	int	i;
	char *var;
	
	i = 0;
	while(glob -> env[i])
	{
		if (!ft_strncmp(glob -> env[i], str, ft_strlen(str)))
		{
			var = ft_strdup(env[i]);
			var += ft_strlen(word);
			break ;
		}
		i++;
	}
	return (var);
}

int main(int ac, char **av, char **env)
{
	int i;
	char *line;

	(void)av;
	(void)env;
	if (ac > 1)
		return(0);
	i = 0;
	line = readline("obeaj->");
	while (line)
	{
		if (*line)
			add_history(line);
		if (!ft_strncmp(line, "exit", 4))
		 {
			write (1, "exit\n", 5); 
			return (0);
		 }   
		if (!ft_strncmp(line, "pwd", 3))
			pwd_cmd();
		line =  readline("obeaj->");
		// runcmd(parsing(line));
	}
	return (0);
}