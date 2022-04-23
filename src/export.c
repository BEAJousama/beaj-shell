/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imabid <imabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:45:50 by obeaj             #+#    #+#             */
/*   Updated: 2022/04/23 23:22:35 by imabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int					if_egal(char *arg)
{
	int				i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
			return (1);
		i++;
	}
	return (0);
}
int					if_plusegal(char *arg)
{
	int				i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '+' && arg[i + 1] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	export_print(t_venv **ve)
{
	t_venv *venv;
	venv = *ve;
	
	while (venv)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(venv->key, 1);
		if(glob.g == 1 && *venv->value == '\0')
		{
			ft_putstr_fd("=", 1);
			ft_putstr_fd("\"", 1);
			ft_putstr_fd("\"", 1);
		}
		if(*venv->value != '\0')
		{
			ft_putstr_fd("=", 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd(venv->value, 1);
		if(*venv->value != '\0')
		{
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
		venv = venv->next;
	}
}

void	sort_env( t_venv **venv)
{
	char	*tmp;
	char	*tmpv;
	t_venv	*j;
	t_venv	*i;

	i = *venv;
	while (i)
	{
		j = i->next;
		while (j)
		{
			if (ft_strcmp(i->key, j->key) > 0)
			{
				// tmp = ft_strdup(i -> key);
				// free(i -> key);
				// i -> key = ft_strdup(j -> key); 
				// free(j -> key);
				// j -> key = ft_strdup(tmp);
				// free(tmp);

				// tmpv = ft_strdup(i -> value);
				// free(i -> value);
				// i -> value = ft_strdup(j -> value); 
				// free(j -> value);
				// j -> value = ft_strdup(tmpv);
				// free(tmpv);
				tmp = i -> key;
				i -> key = j -> key;
				j -> key = tmp;

				tmpv = i -> value;
				i -> value = j -> value; 
				j -> value = tmpv;	
			}
			j = j->next;
		}
		i = i->next;
	}
	export_print(venv);
}

void	export_go(t_mini *mini,int i)
{
	char *key;
	char *val;

	key = get_key(mini->echo[i]);
	val = get_value(mini->echo[i]);
	add_global_venv(key, val, glob.venv);
}

void	env_go(char *arg)
{
	char *key;
	char *val;
	key = get_key(arg);
	val = get_value(arg);
	add_global_venv(key, val, glob.ennv);
}

void	addto_key(char *arg)
{
	char *key;
	char *cokey;
	char *val;
	char *v;

	int i = -1;
	int j = 0;
	key = get_key(arg);
	val = get_value(arg);
	key = malloc(ft_strlen(key));

	while(arg[++i])
	{
		if(arg[i] != '+' && arg[i + 1] != '=')
			key[j] = arg[i];
		j++;
	}
	v = get_venv(key,glob.venv);
	if(v)
	{
		cokey = ft_strjoin(get_venv(key,glob.venv),val);
		add_global_venv(key, cokey, glob.ennv);
		add_global_venv(key, cokey, glob.venv);
	}
	else
	{
		add_global_venv(key, val, glob.ennv);
		add_global_venv(key, val, glob.venv);
	}
}
void	check_args(t_mini *mini)
{
	int i;
	int j;
	
	i = 1;
	j = 0;
	while (mini->echo[i])
	{
		if(ft_isalpha(mini->echo[i][0]) || mini->echo[i][0] == '_')
		{
			if(if_egal(mini->echo[i]) && !if_plusegal(mini->echo[i]))
			{
				env_go(mini->echo[i]);
				export_go(mini,i);
			}
			if(if_plusegal(mini->echo[i]))
				addto_key(mini->echo[i]);
			if(!if_egal(mini->echo[i]))
				export_go(mini,i);
		}
		else
		{
			print_error("export: `", mini->echo[i], "': not a valid identifier\n");
		}
		if(if_egal(mini->echo[i]))
			glob.g = 1;
		i++;
	}
}
void	export_cmd(t_mini *mini)
{
	if (!mini->echo[1])
	{	
		sort_env(glob.venv);
	}
	else
	{
		check_args(mini);
	}
}
