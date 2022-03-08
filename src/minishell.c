/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imabid <imabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 10:28:27 by obeaj             #+#    #+#             */
/*   Updated: 2022/03/08 18:52:09 by imabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **env)
{
	int i;
	char *line;
	char **paths;
	char	**cmd1;
	char	*path1;
	int		status;

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
		else
		{
			int pid = fork();
			if(pid == 0){
			paths = ft_split(find_path(env), ':');
			cmd1 = ft_split(line, ' ');
			path1 = get_path(paths, cmd1);
			execve(path1,cmd1,env);
			}
			wait(&status);
		}
		line =  readline("obeaj->");
		// runcmd(parsing(line));
	}
	return (0);
}