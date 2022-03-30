/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 17:31:39 by obeaj             #+#    #+#             */
/*   Updated: 2022/03/30 02:41:39 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_wildcard(char *word, char **env)
{
	struct dirent	*de;
	int				len;
    DIR				*dr;
	char			*new;
	
	dr = opendir(".");
	word = (ft_strtok(word, '*'));
	len = ft_strlen(word);
	new = ft_strdup("\0");
	
    if (dr == NULL)
    {
        printf("Could not open current directory" );
    }
    while ((de = readdir(dr)) != NULL)
	{
        if (ft_strnstr(de -> d_name, "\0", len))
		{
			new = ft_strjoin1(new, de->d_name);
		}
	}
    // closedir(dr);
	return (new); 
}

char	*expand_dollar(char *word, char **env)
{
	int	i;
	char *var;	
	i = 0;
	while(env[i])
	{
		if (!ft_strncmp(env[i], word + 1, ft_strlen(word) - 1))
		{
			var = ft_strdup(env[i]);
			var += ft_strlen(word);
			break ;
		}
		i++;
	}
	return (var);
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
			home = ft_strdup(env[i]);
			home += 5;
			break ;
		}
		i++;
	}
	newword = ft_strjoin(home, word + 1);
	free(home - 5);
	return (newword);
}

t_token **expander(t_token **tokens)
{
	
}

int main(int ac, char **av, char **env)
{
	char word[200] = "*.c";
	char *new;
	new = expand_wildcard(word, env);
	// expand_wildcard(word, env);
	printf("%s\n", new);
}