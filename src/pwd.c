/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imabid <imabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:45:53 by obeaj             #+#    #+#             */
/*   Updated: 2022/04/22 17:40:14 by imabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd_cmd(void)
{
	char	*pwd;

	if (getcwd(NULL, 0))
		pwd = getcwd(NULL, 0);
	else
		pwd = get_venv("PWD", glob.ennv);
	ft_putstr_fd(pwd, 1);
	ft_putchar_fd('\n', 1);
}
