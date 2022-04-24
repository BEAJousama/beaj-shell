/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imabid <imabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:45:38 by obeaj             #+#    #+#             */
/*   Updated: 2022/04/24 16:18:56 by imabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *f, char *m, char *l)
{
	ft_putstr_fd(f, 2);
	ft_putstr_fd(m, 2);
	ft_putstr_fd(l, 2);
}

void	old_pwd(void)
{
	char	*val;

	if (getcwd(NULL, 0))
		val = getcwd(NULL, 0);
	else
		val = get_venv("PWD", glob.ennv);
	add_global_venv("OLDPWD", val, glob.ennv);
	add_global_venv("OLDPWD", val, glob.venv);
}

void	pwd_pwd(void)
{
	char	*val;

	val = getcwd(NULL, 0);
	add_global_venv("PWD", val, glob.ennv);
	add_global_venv("PWD", val, glob.venv);
}

void	cd_cmd(t_m *m)
{
	char	*home;

	old_pwd();
	if (!m->args[1] || !ft_strcmp(m->args[1], "~")
		|| !ft_strcmp(m->args[1], "--"))
	{
		home = get_venv("HOME", glob.venv);
		if (!home)
		{
			ft_putstr_fd("mshell: cd: HOME not set\n", 2);
			return ;
		}
		m->args[1] = ft_strdup(get_venv("HOME", glob.venv));
	}
	if (chdir(m->args[1]) == -1)
		print_error("cd: ", m->args[1], ": No such file or directory\n");
	pwd_pwd();
}
