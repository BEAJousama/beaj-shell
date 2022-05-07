/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:45:53 by obeaj             #+#    #+#             */
/*   Updated: 2022/05/07 16:40:13 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd_cmd(void)
{
	char	*pwd;
	char	*s;

	g_glob.status = 0;
	s = getcwd(NULL, 0);
	if (s)
		pwd = getcwd(NULL, 0);
	else
		pwd = get_venv("PWD", g_glob.ennv);
	ft_putstr_fd(pwd, 1);
	ft_putchar_fd('\n', 1);
	free(pwd);
	free(s);
}
