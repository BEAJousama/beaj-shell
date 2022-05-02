/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 00:11:30 by obeaj             #+#    #+#             */
/*   Updated: 2022/05/02 01:46:10 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_redir(t_cmd	*cmd)
{
	int	fd;
	int	status;

	if (fork() == 0)
	{
		close(cmd ->fd);
		fd = open(cmd->file, cmd->mode, 0666);
		if (fd < 0)
		{
			printf("open %s failed\n", cmd->file);
			exit(1);
		}
		dup2(fd, cmd->fd);
		runcmd(cmd->right);
		close(fd);
		exit(1);
	}
	wait(&status);
	return (0);
}

int	run_and(t_cmd	*cmd)
{
	int	status;
	int	pid;

	pid = fork();
	if (pid == 0)
		runcmd(cmd->left);
	wait(&status);
	if (cmd ->right && cmd->right->argv[0]
		&& g_glob.status == 0)
		runcmd(cmd->right);
}

int	run_or(t_cmd	*cmd)
{
	int	status;
	int	pid;

	pid = fork();
	if (pid == 0)
		runcmd(cmd->left);
	wait(&status);
	if (cmd ->right && cmd->right->argv[0]
		&& g_glob.status != 0)
		runcmd(cmd->right);
}

int	run_back(t_cmd	*cmd)
{
	close(cmd->fd);
	if (open(cmd->file, cmd->mode, 0666) < 0)
	{
		printf("open %s failed\n", cmd->file);
		exit(1);
	}
	runcmd(cmd->right);
	return (0);
}

int	run_sub(t_cmd	*cmd)
{
	runcmd(cmd->right);
	return (0);
}
