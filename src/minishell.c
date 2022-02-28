/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 10:28:27 by obeaj             #+#    #+#             */
/*   Updated: 2022/02/28 12:39:11 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **env)
{
    int i;
    char *line;

    (void)av;
    (void)env;
    if (ac > 1)
        return(0);
    i = 0;
    line = readline("obeaj->");
    while (line)
    {
        add_history(line);
        line =  readline("obeaj->");
        // parsing(line);
    }
    return (0);
}