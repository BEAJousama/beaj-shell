/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imabid <imabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 10:29:51 by obeaj             #+#    #+#             */
/*   Updated: 2022/03/24 18:34:03 by imabid           ###   ########.fr       */
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
typedef struct s_export {
	char **tab;
}	t_export;

typedef struct s_mini
{
	char		**cmd;
	char		*path;
	char		**env;
	char		**env_g;
	int			f1;
	int			f2;
	int			a;
	int			aca;
	int			fd[2];
	int 		i;
	char 		*line;
	char 		**paths;
	char		**cmd1;
	char		*path1;
	char 		**echo;
	int			status;
	t_export 	export;
}	t_mini;

void pwd_cmd(void);
char	*find_path(char **str);
char	*get_path(char	**paths, char	**cmd);
void    echo_cmd(char **cmd);
void cd_cmd(char *cmd);
void    export_cmd(t_mini *mini);
#endif

