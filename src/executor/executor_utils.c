/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 20:25:54 by obeaj             #+#    #+#             */
/*   Updated: 2022/04/27 21:51:00 by obeaj            ###   ########.fr       */
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
