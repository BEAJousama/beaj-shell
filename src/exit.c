/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imabid <imabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:45:47 by obeaj             #+#    #+#             */
/*   Updated: 2022/04/28 14:44:28 by imabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// void		ft_exit(t_mini *m)
// {
// 	char *arg1;

// 	m->v.i = 0;
// 	m->v.j = -1;
// 	m->shell_lvl--;
// 	ft_putstr_fd("exit\n", 1);
// 	if (m->args[2] && m->args_num > 1)
// 	{
// 		g_v.exit_status = 1;
// 		arg1 = ft_strdup("0");
// 		ft_error("exit", ": too many argument", "\n");
// 	}
// 	else if (m->args[1])
// 	{
// 		ft_exit_3(m);
// 		if (m->v.i == (int)ft_strlen(m->args[1]))
// 			arg1 = ft_strdup(m->args[1]);
// 	}
// 	else
// 		arg1 = ft_strdup("0");
// 	if (m->shell_lvl >= m->first_lvl)
// 		ft_exit_1(m);
// 	else if (m->shell_lvl < m->first_lvl)
// 		ft_exit_2(arg1);
// }

void    exit_cmd(t_m *m)
{
    m->shlvl--;
}