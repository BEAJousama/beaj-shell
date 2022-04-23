/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imabid <imabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 17:28:10 by obeaj             #+#    #+#             */
/*   Updated: 2022/04/20 17:19:13 by imabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_glob glob;

void	show_vars(void)
{
	t_venv *var;

	var = (*glob.ennv);
	while (var)
	{
		ft_putstr_fd(var->key, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd(var->value, 1);
		ft_putstr_fd("\n", 1);
		var = var -> next;
	}
}

// t_group	**init_group(t_group **group)
// {
// 	group = malloc(sizeof(t_group *));
// 	if (!group)
// 		return (NULL);
// 	*group = NULL;
// 	return (group);
// }

// t_group	*new_gnode(char *data)
// {
// 	t_group	*group;
	
// 	group = malloc(sizeof(t_group) * 1);
// 	group -> data = data;
// 	group -> next = NULL; 
// 	return (group);
// }

// void	free_group(t_group **group)
// {
// 	t_group *first;

// 	first = *group;
// 	while (first)
// 	{
// 		free(first);
// 		first = first -> next;
// 	}
// 	free(*group);
// }

// void	gnode_add_back(t_group **group, t_group *new)
// {
// 	t_group	*first;

// 	if (!group)
// 		return ;
// 	if (!*group)
// 		*group = new;
// 	else
// 	{
// 		first = *group;
// 		while (first -> next != NULL)
// 			first = first -> next;
// 		first -> next = new;
// 	}
// }
