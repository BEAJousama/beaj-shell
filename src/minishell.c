/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 10:28:27 by obeaj             #+#    #+#             */
/*   Updated: 2022/04/03 14:38:03 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_glob	glob = {.venv = NULL, .vars = NULL, .status = 0};

char	*get_key(char *env)
{
	int	len;

	len = 0;
	while (env[len] && env[len] != '=')
		len++;
	return (ft_strndup(env, len + 1));
}

char	*get_value(char *env)
{
	int	len;

	len = 0;
	while (env[len] && env[len] != '=')
		len++;
	return (ft_strdup(env + len + 1));
}

t_venv	**init_venv(t_venv **venv)
{
	venv = malloc(sizeof(t_venv *));
	if (!venv)
		return (NULL);
	*venv = NULL;
	return (venv);
}

t_venv	*new_venv(char *key, char *value)
{
	t_venv	*venv;
	
	venv = malloc(sizeof(t_venv) * 1);
	venv -> key = ft_strdup(key);
	venv -> value = ft_strdup(value);
	venv -> next = NULL; 
	return (venv);
}

void	venv_add_back(t_venv **venv, t_venv *new)
{
	t_venv	*first;

	if (!venv)
		return ;
	if (!*venv)
		*venv = new;
	else
	{
		first = *venv;
		while (first -> next != NULL)
			first = first -> next;
		first -> next = new;
	}
}


void	set_global_env(char **env)
{
	int		len;
	t_venv	*new;
	
	glob.venv = init_venv(glob.venv);

	len = 0;
	while (*(env + len))
	{
		new = new_venv(get_key(*(env + len)), get_value(*(env + len)));
		// printf("%s", new -> key);
		venv_add_back(glob.venv, new);
		len++;
	}

}

// void	set_global_vars(char **env)
// {
// 	int		len;

// 	len = 0;
// 	while (*env[len])
// 	{
// 		glob.venv = init_env();
// 		len++;
// 	}
// }

// char	*get_env(char *str)
// {
// 	int	i;
// 	char *var;
	
// 	i = 0;
// 	while(glob.env[i])
// 	{
// 		if (!ft_strncmp(glob.env[i], str, ft_strlen(str)))
// 		{
// 			var = ft_strdup(env[i]);
// 			var += ft_strlen(word);
// 			break ;
// 		}
// 		i++;
// 	}
// 	return (var);
// }

int main(int ac, char **av, char **env)
{
	int i;
	char *line;

	(void)av;
	(void)env;
	set_global_env(env);
	if (ac > 1)
		return(0);
	i = 0;
	while (*glob.venv)
	{

		printf("%s = %s \n", (*glob.venv)->key , (*glob.venv)->value);
		*glob.venv = (*glob.venv)->next;
	}
	// line = readline("obeaj->");
	// while (line)
	// {
	// 	if (*line)
	// 		add_history(line);
	// 	if (!ft_strncmp(line, "exit", 4))
	// 	 {
	// 		write (1, "exit\n", 5); 
	// 		return (0);
	// 	 }   
	// 	if (!ft_strncmp(line, "pwd", 3))
	// 		pwd_cmd();
	// 	line =  readline("obeaj->");
	// 	// runcmd(parsing(line));
	// }
	return (0);
}