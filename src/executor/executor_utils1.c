/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 17:46:07 by obeaj             #+#    #+#             */
/*   Updated: 2022/05/05 20:43:22 by obeaj            ###   ########.fr       */
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
		exit(g_glob.status);
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

static void	print_glob(int p)
{
	if (((!g_glob.cmd->argv[1]
				&& g_glob.buff && *g_glob.buff && (*g_glob.buff)-> value)))
	{
		while (*g_glob.buff)
		{
			ft_putstr_fd((*g_glob.buff)->value, p);
			ft_putchar_fd('\n', p);
			(*g_glob.buff) = (*g_glob.buff)->next;
		}
	}
}

int	run_hdoc(t_token *token)
{
	char	*line;
	int		i;
	int		p[2];

	i = 0;
	pipe(p);
	if (g_glob.buff)
		free_glob(g_glob.buff);
	g_glob.buff = NULL;
	g_glob.buff = init_venv(g_glob.venv);
	line = readline("-> ");
	while (line)
	{
		if (!ft_strcmp(line, token -> data))
			break ;
		add_global_venv(ft_itoa(i), line, g_glob.buff);
		i++;
		line = readline("-> ");
	}
	if (fork() == 0)
	{
		print_glob(p[1]);
		dup2(p[1], 1);
		close(p[1]);
		close(p[0]);
		exit(1);
	}
	dup2(p[0], 0);
	return (0);
}
