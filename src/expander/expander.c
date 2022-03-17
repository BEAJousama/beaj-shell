/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 17:31:39 by obeaj             #+#    #+#             */
/*   Updated: 2022/03/17 20:22:42 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char expand_wildcard(char *word)
{
	
}
char	*expand_tilde(char *word, char **env)
{
	int	i;
	char *home;
	char *newword;
	
	i = 0;
	while(env[i])
	{
		if (!ft_strncmp(env[i], "HOME=",5))
		{
			// printf("%s\n", env[i]);
			home = ft_strdup(env[i]);
			home += 5;
			printf("%s\n", home);
			break ;
		}
		i++;
	}
	newword = ft_strjoin(home, word + 1);
	return (newword);
}
int main(int ac, char **av, char **env)
{
	char word[200] = "~/lsldd";
	char *new;
	// printf("%s", 
	new = expand_tilde(word, env);
	// printf("%s\n", ft_strtok(word, ' '));
	// printf("%s\n", ft_strtok(NULL, ' '));
	printf("%s\n", new);
}