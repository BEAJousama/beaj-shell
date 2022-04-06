/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 17:28:10 by obeaj             #+#    #+#             */
/*   Updated: 2022/04/05 18:49:07 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_strlen1(const	char *s)
{
	size_t	len;

	len = 0;
	while (*s++)
		len++;
	return (len);
}

char	*ft_strjoin1(char *s1, char *s2)
{
	int		len_tot;
	char	*s;

	if (!s2 || !s1)
		return (NULL);
	len_tot = ft_strlen1(s1) + ft_strlen1(s2) + 2;
	s = (char *)malloc(len_tot * sizeof(char));
	if (!s)
		return (NULL);
	while (*s1)
		*s++ = *s1++;
	*s++ = ' ';
	while (*s2)
		*s++ = *s2++;
	*s = '\0';
	return (s - len_tot + 1);
}

t_group	**init_group(t_group **group)
{
	group = malloc(sizeof(t_group *));
	if (!group)
		return (NULL);
	*group = NULL;
	return (group);
}

t_group	*new_gnode(char *data)
{
	t_group	*group;
	
	group = malloc(sizeof(t_group) * 1);
	group -> data = data;
	group -> next = NULL; 
	return (group);
}

void	gnode_add_back(t_group **group, t_group *new)
{
	t_group	*first;

	if (!group)
		return ;
	if (!*group)
		*group = new;
	else
	{
		first = *group;
		while (first -> next != NULL)
			first = first -> next;
		first -> next = new;
	}
}
