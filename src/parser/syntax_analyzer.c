/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyzer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 18:59:44 by obeaj             #+#    #+#             */
/*   Updated: 2022/03/12 19:19:00 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void analyzer(t_token **tokens)
{
    t_token *first;
    t_token *next;
    t_token *prev;

    first = *tokens;
    while (first)
    {
        if (!ft_strncmp(first->type , "OPAR", 4))
        {
            next = first;
            prev = first;
            while (next -> next)
            {
                if (ft_strncmp(first->type , "OPAR", 4))
            }
        }
    }
}