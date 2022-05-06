/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 10:29:51 by obeaj             #+#    #+#             */
/*   Updated: 2022/05/06 17:13:02 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include "libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdbool.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>
# include "parser.h"
# include "tokenizer.h"
# include "expander.h"
# include "executor.h"
# include "gc.h"

extern t_glob	g_glob;

void	free_tab(char **tab);

#endif
