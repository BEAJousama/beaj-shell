/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imabid <imabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 10:29:51 by obeaj             #+#    #+#             */
/*   Updated: 2022/04/29 15:15:17 by imabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include <unistd.h>
# include <stdio.h>
# include "expander.h"
// # include "parser.h"

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

extern t_glob glob;

typedef struct s_m
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
	char 		**args;
	int			status;
	char	*key;
	char	*cokey;
	char	*val;
	char	*v;
	int		shlvl;
	int		fshlvl;
	t_export 	export;
}	t_m;

void pwd_cmd(void);
char	*find_path(char **str);
char    *get_path(char *cmd);
void    echo_cmd(char **cmd);
void	cd_cmd(char **args);
void	export_cmd(char **args);
void	env_cmd(char **args);
void    exit_cmd(t_m *m);
void	unset_cmd(char **args);
void	del_venv(char *key);
void	del_ennv(char *key);
void	show_vars(void);
void print_error(char *f, char *m, char *l);
int	if_egal(char *arg);
int	if_plusegal(char *arg);
void	print_quotes(void);
void	export_print(t_venv **ve);
void	sort_env( t_venv **venv);
void	env_go(char *arg);
#endif

