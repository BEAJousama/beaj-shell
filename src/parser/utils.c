/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 14:02:51 by obeaj             #+#    #+#             */
/*   Updated: 2022/03/30 02:49:48 by obeaj            ###   ########.fr       */
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

int	peek(char **line, char *eline, char *toks)
{
	char	*s;

	s = *line;
	while (s < eline && ft_strchr(SPACES, *s))
		s++;
	*line = s;
	return (*s && ft_strchr(toks, *s));
}