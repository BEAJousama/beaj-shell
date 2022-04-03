/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 14:02:51 by obeaj             #+#    #+#             */
/*   Updated: 2022/04/03 21:26:01 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_error(char *str, char *data)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(data, 2);
	ft_putchar_fd('\n', 2);
	return (1);
}

void	freetab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
	{
		free(tab[i]);
	}
	free(tab);
}

int	peek(char **line, char *toks)
{
	char	*s;

	s = *line;
	*line = s;
	return (*s && ft_strchr(toks, *s));
}
