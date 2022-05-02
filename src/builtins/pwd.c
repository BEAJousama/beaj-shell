/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:45:53 by obeaj             #+#    #+#             */
/*   Updated: 2022/05/01 18:03:30 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd_cmd(void)
{
	char	*pwd;

	g_glob.status = 0;
	if (getcwd(NULL, 0))
		pwd = getcwd(NULL, 0);
	else
		pwd = get_venv("PWD", g_glob.ennv);
	ft_putstr_fd(pwd, 1);
	ft_putchar_fd('\n', 1);
}
