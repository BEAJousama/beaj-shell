/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 17:46:07 by obeaj             #+#    #+#             */
/*   Updated: 2022/05/02 23:55:35 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipe(int fds[2])
{
	close(fds[0]);
	close(fds[1]);
}

pid_t	run_pipe_util(t_cmd *cmd, int fd[2], int s)
{
	pid_t		pid;
	int			i;
	int			io;
	t_cmd		*cmd1;

	cmd1 = cmd ->left;
	i = STDOUT_FILENO;
	io = STDOUT_FILENO;
	if (s & 2)
	{
		i = STDIN_FILENO;
		io = STDIN_FILENO;
		cmd1 = cmd->right;
	}
	pid = ft_fork();
	if (pid == 0)
	{
		dup2(fd[i], io);
		close_pipe(fd);
		runcmd(cmd1);
	}
	return (pid);
}

int	ft_pipe(int fildes[2])
{
	int	ret;

	ret = pipe(fildes);
	if (ret == -1)
		print_error("pipe", strerror(errno));
	return (ret);
}
