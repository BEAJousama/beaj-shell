/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:46:14 by obeaj             #+#    #+#             */
/*   Updated: 2022/04/28 01:27:17 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_builtin(char *cmd, char **argv)
{
	if (!ft_strncmp(cmd, "echo", sizeof("echo") + 1))
		return (echo(argv), true);
	else if (!ft_strncmp(cmd, "cd", sizeof("cd") + 1))
		return (cd(argv, &g_glob.venv), true);
	else if (!ft_strncmp(cmd, "pwd", sizeof("pwd") + 1))
		return (pwd(argv, &g_glob.venv), true);
	else if (!ft_strncmp(cmd, "export", sizeof("export") + 1))
		return (export(argv, &g_glob.venv), true);
	else if (!ft_strncmp(cmd, "unset", sizeof("unset") + 1))
		return (unset(argv, &g_glob.venv), true);
	else if (!ft_strncmp(cmd, "env", sizeof("env") + 1))
		return (ft_env(argv, &g_glob.venv), true);
	else if (!ft_strncmp(cmd, "exit", sizeof("exit") + 1))
		return (ft_exit(argv), true);
	return (false);
}

void	run_exec(t_cmd *cmd)
{
	int	pid;

	if (is_built(cmd ->argv[0], cmd ->argv))
		return ;
	pid = fork();
	if (pid == -1)
		return ;
	else if (pid == 0)
		ft_execve(cmd -> argv);
}

int	runcmd(t_cmd *cmd)
{
	t_cmd	*root;

	root = cmd;
	if (root -> type & AST_REDIR)
		run_redir(root);
	else if (root ->type & AST_SC)
		run_list(root);
	else if (root ->type & AST_PIPE)
		run_pipe(root);
	else if (root ->type & AST_AND)
		run_and(cmd);
	else if (root ->type & AST_OR)
		run_or(cmd);
	else if (root ->type & AST_BG)
		run_back(cmd);
	else if (root ->type & AST_EXEC)
		run_exec(cmd);
	return (0);
}
