/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 00:11:30 by obeaj             #+#    #+#             */
/*   Updated: 2022/04/30 17:17:22 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_redir(t_cmd	*cmd)
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

int	run_and(t_cmd	*cmd)
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

int	run_or(t_cmd	*cmd)
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
