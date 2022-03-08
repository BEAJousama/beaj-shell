/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:46:21 by obeaj             #+#    #+#             */
/*   Updated: 2022/03/08 10:50:56 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int n_tokens(char **line, char *eline)
// {
// 	char	*s;
// 	int		i;

// 	i = 0;
// 	s = *line;
// 	while (s < eline)
// 	{
// 		if (ft_strchr(TERMES, *s))
// 			i++;
// 		s++;
// 	}
// 	return (2 * i + 1);
// }

int	peek(char **line, char *eline, char *toks)
{
  char	*s;

  s = *line;
  while (s < eline && strchr(SPACES, *s))
    s++;
  *line = s;
  return (*s && strchr(toks, *s));
}

char	tokenizer (char **line, char *eline, char **tok, char **etok)
{
	char	*s;
	char	r;
		
	s = *line;
	while (s < eline && ft_strrchr(SPACES, *s))
		s++;
	if (tok)
		*tok = s;
	r = *s;
	if (ft_strchr(TERMES_1, *s))
		s++;
	else if (*s == '>')
	{
		s++;
		if (*s == '>')
			r = '+';
		s++;
	}
	else if (*s == '<')
	{
		s++;
		if (*s == '<')
			r = '-';
		s++;
	}
	else 
	{
		r = 'o';
		while (s < eline && !ft_strchr(TERMES, *s))
			s++;
	}
	if (etok)
		*etok = s;
	*line = s;
	return (r);
}
