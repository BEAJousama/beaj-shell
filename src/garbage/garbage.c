/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 16:47:17 by obeaj             #+#    #+#             */
/*   Updated: 2022/05/06 18:07:41 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_gc	**init_gc(void)
{
	t_gc	**gc;

	gc = malloc(sizeof(t_gc *));
	*gc = NULL;
	return (gc);
}

t_gc	*new_gcnode(void *str)
{
	t_gc	*gc;

	gc = malloc(sizeof(t_gc));
	gc->s = str;
	gc -> next = NULL;
	return (gc);
}

void	gc_add_back(t_gc *new)
{
	t_gc	*first;
	t_gc	**gc;

	gc = g_glob.gc;
	if (!gc)
		return ;
	if (*gc)
	{
		first = *gc;
		while (first -> next)
			first = first -> next;
		first -> next = new;
	}
	else
		*gc = new;
}

void	free_gc(t_gc **gc)
{
	t_gc	*g;

	g = *gc;
	while (g)
	{
		if (g->s)
			free(g->s);
		g -> s = NULL;
		if (g)
			free(g);
		g = NULL;
		g = g ->next;
	}
}
