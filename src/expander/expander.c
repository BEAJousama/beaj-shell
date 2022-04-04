/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 17:31:39 by obeaj             #+#    #+#             */
/*   Updated: 2022/04/04 18:26:21 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_wildcard(char *word, char **env)
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
			new = ft_strjoin1(new, de->d_name);
	}
    // closedir(dr);
	return (new); 
}

static t_token	**expand_dollar(t_token **tokens)
{
	t_token *first;
	char	*data;
	
	first = *tokens;
	while (first)
	{
		if (first -> tok & VAR)
		{
			data = get_venv(first -> data);
			free(first -> data);
			first -> data = data;
			first -> tok = STR;
		}
		else if (first -> tok & TLD)
		{
			free(first -> data);
			first -> data = get_venv("HOME");
			first -> tok = STR;
		}
		if (!first -> data)
			del_token_0(first);
		first = first -> next;
	}
	return (tokens);
}

t_token **expander(t_token **tokens)
{
	tokens = expand_dollar(tokens);
	return (tokens);	
}
