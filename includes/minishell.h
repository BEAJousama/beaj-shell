/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 10:29:51 by obeaj             #+#    #+#             */
/*   Updated: 2022/04/13 16:31:17 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include "libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include "parser.h"
# include "tokenizer.h"
# include "expander.h"

typedef struct s_cmd
{
	int type;
	struct s_cmd *left;
	struct s_cmd *right;
}	t_cmd;

typedef struct s_execcmd {
	int type;
	char *argv[10];
}	t_execcmd;

typedef struct s_redircmd {
	int type;
	struct s_cmd *cmd;
	char *file;
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
#endif

