/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:45:38 by obeaj             #+#    #+#             */
/*   Updated: 2022/04/30 18:15:35 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error_(char *f, char *m, char *l)
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
		val = get_venv("PWD", g_glob.ennv);
	add_global_venv("OLDPWD", val, g_glob.ennv);
	add_global_venv("OLDPWD", val, g_glob.venv);
}

void	pwd_pwd(void)
{
	char	*val;

	val = getcwd(NULL, 0);
	add_global_venv("PWD", val, g_glob.ennv);
	add_global_venv("PWD", val, g_glob.venv);
}

void	cd_cmd(char **args)
{
	char	*home;

	g_glob.status = 0;
	old_pwd();
	if (!args[1] || !ft_strcmp(args[1], "~")
		|| !ft_strcmp(args[1], "--"))
	{
		home = get_venv("HOME", g_glob.venv);
		if (!home)
		{
			ft_putstr_fd("mshell: cd: HOME not set\n", 2);
			g_glob.status = 1;
			return ;
		}
		args[1] = ft_strdup(get_venv("HOME", g_glob.venv));
	}
	if (chdir(args[1]) == -1)
	{
		g_glob.status = 1;
		print_error_("cd: ", args[1], ": No such file or directory\n");
	}
	pwd_pwd();
}
