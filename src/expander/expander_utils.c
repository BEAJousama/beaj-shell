/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 17:28:10 by obeaj             #+#    #+#             */
/*   Updated: 2022/04/24 01:36:35 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_glob	g_glob;

void	show_vars(void)
{
	t_venv	*var;

	var = (*g_glob.venv);
	while (var)
	{
		printf("%s=%s\n", var->key, var->value);
		var = var -> next;
	}
}

t_group	**init_group()
{
	t_group	**group;
	
	group = malloc(sizeof(t_group *));
	if (!group)
		return (NULL);
	return (group);
}

t_group	*new_gnode(char *data)
{
	t_group	*group;

	group = malloc(sizeof(t_group));
	group -> data = ft_strdup(data);
	group -> next = NULL;
	return (group);
}

void	free_group(t_group **group)
{
	if (!group)
		return ;
	if (group && *group == NULL)
	{
		free(group);
		return ;
	}
	while (*group != NULL)
	{
		if ((*group)->data)
			free((*group)->data);
		free(*group);
		(*group) = (*group)->next;
	}
	free(group);
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
