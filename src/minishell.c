/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 10:28:27 by obeaj             #+#    #+#             */
/*   Updated: 2022/04/03 23:32:29 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **env)
{
	int i;
	char *line;

	(void)av;
	(void)env;
	if (ac > 1)
		return(0);
	i = 0;
	while (*glob.venv)
	{

		printf("%s = %s \n", (*glob.venv)->key , (*glob.venv)->value);
		*glob.venv = (*glob.venv)->next;
	}
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