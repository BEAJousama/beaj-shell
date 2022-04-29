/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:46:14 by obeaj             #+#    #+#             */
/*   Updated: 2022/04/29 16:24:18 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_builtin(char *cmd, char **argv)
{
	if (!ft_strncmp(cmd, "echo", sizeof("echo") + 1))
		return (echo_cmd(argv), true);
	else if (!ft_strncmp(cmd, "cd", sizeof("cd") + 1))
		return (cd_cmd(argv), true);
	else if (!ft_strncmp(cmd, "pwd", sizeof("pwd") + 1))
		return (pwd_cmd(), true);
	else if (!ft_strncmp(cmd, "export", sizeof("export") + 1))
		return (export_cmd(argv), true);
	else if (!ft_strncmp(cmd, "unset", sizeof("unset") + 1))
		return (unset_cmd(argv), true);
	else if (!ft_strncmp(cmd, "env", sizeof("env") + 1))
		return (env_cmd(argv), true);
	// else if (!ft_strncmp(cmd, "exit", sizeof("exit") + 1))
	// 	return (exit_cmd(argv), true);
	return (false);
}

void	run_exec(t_cmd *cmd)
{
	int	ret;

	if (is_builtin(cmd ->argv[0], cmd ->argv))
		return ;
	ret = ft_execve(cmd -> argv);
	if (ret == -1)
		return ;
	if (ret == -2)
		return ;
	// exit(1);
}

void	run_list(t_cmd *cmd)
{
	if(fork() == 0)
		runcmd(cmd->left);
	waitpid(-1, NULL, 0);
	runcmd(cmd->right);
}

void	run_pipe(t_cmd *cmd)
{
	int	p[2];

/*
	if (pipe(p) < 0)
*/
	pipe(p);
	if (fork() == 0)
	{
		close(1);
		dup(p[1]);
		close(p[0]);
		close(p[1]);
		runcmd(cmd->left);
	}
	if (fork())
	{
		close(0);
		dup(p[0]);
		close(p[0]);
		close(p[1]);
		runcmd(cmd->right);
	}
	close(p[0]);
	close(p[1]);
	waitpid(-1, NULL, 0);
}

int	runcmd(t_cmd *cmd)
{
	t_cmd	*root;
	
	if (!cmd)
		return (1);
	root = cmd;
	// else if (root ->type & AST_AND)
	// 	run_and(root);
	// else if (root ->type & AST_OR)
	// 	run_or(root);
	// else if (root ->type & AST_BG)
	// 	run_back(root);
	if (root ->type & AST_EXEC)
		run_exec(root);
	else if (root ->type & AST_SC)
		run_list(root);
	else if (root -> type & AST_REDIR)
		run_redir(root);
	else if (root ->type & AST_PIPE)
		run_pipe(root);
	return (0);
}
