/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imabid <imabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 10:29:51 by obeaj             #+#    #+#             */
/*   Updated: 2022/03/08 18:24:43 by imabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include <unistd.h>
# include <stdio.h>
# include "parser.h"

typedef struct s_cmd
{
		int type;
}	t_cmd;

typedef struct s_execcmd {
	int type;
	char *argv[10];
	char *eargv[10];
}	t_execcmd;

typedef struct s_redircmd {
	int type;
	struct s_cmd *cmd;
	char *file;
	char *efile;
	int mode;
	int fd;
}	t_redircmd;

typedef struct s_pipecmd {
	int type;
	struct s_cmd *left;
	struct s_cmd *right;
}	t_pipecmd;

typedef struct s_listcmd {
	int type;
	struct s_cmd *left;
	struct s_cmd *right;
}	t_listcmd;

typedef struct s_backcmd {
	int type;
	struct s_cmd *cmd;
}	t_backcmd;

void pwd_cmd(void);
char	*find_path(char **str);
char	*get_path(char	**paths, char	**cmd);

#endif

