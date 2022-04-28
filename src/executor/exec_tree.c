/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 00:11:30 by obeaj             #+#    #+#             */
/*   Updated: 2022/04/28 01:28:23 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_redir(t_cmd	*cmd)
{
	close(cmd->fd);
	if (open(cmd->file, cmd->mode) < 0)
	{
		printf(2, "open %s failed\n", cmd->file);
		exit();
	}
	runcmd(cmd->cmd);
	return (0);
}
