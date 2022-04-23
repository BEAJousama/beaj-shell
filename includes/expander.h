/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imabid <imabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:45:33 by obeaj             #+#    #+#             */
/*   Updated: 2022/04/23 23:19:42 by imabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

typedef struct s_venv
{
	char			*key;
	char			*value;
	struct s_venv	*next;
	int g;
}	t_venv;

typedef struct s_glob
{
	t_venv	**venv;
	t_venv	**vars;
	t_venv	**ennv;
	int		status;
	int		g;
}	t_glob;

t_venv	**set_global_env(char **env, t_venv **ennv);
void	add_global_vars(char *key, char *value);
void	add_global_venv(char *key, char *value,t_venv **all);
void	del_venv(char *key);
void	free_glob(void);
char	*get_venv(char *key,t_venv **all);
char	*get_var(char *key);
char	*get_key(char *env);
void	show_vars(void);
char	*get_value(char *env);
t_venv	**init_venv(t_venv **venv);
t_venv	*new_venv(char *key, char *value);
void	venv_add_back(t_venv **venv, t_venv *new);
// t_group	**init_group(t_group **group);
// t_group	*new_gnode(char *data);
// void	free_group(t_group **group);
// void	gnode_add_back(t_group **group, t_group *new);
// t_token **expander(t_token **tokens);

#endif

