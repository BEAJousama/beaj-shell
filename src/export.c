/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imabid <imabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:45:50 by obeaj             #+#    #+#             */
/*   Updated: 2022/03/27 15:28:37 by imabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_env(t_mini *mini)
{
	int	l;
	int	i;

	l = 0;
	i = 0;
	while (mini->env_g[l])
		l++;
	mini->export.tab = (char **)malloc(sizeof(char *) * (l + 1));
	while (mini->env_g[i])
	{
		mini->export.tab[i] = ft_strdup(mini->env_g[i]);
		i++;
	}
	mini->export.tab[i] = NULL;
	return (mini->export.tab);
}

void	export_print(t_mini *mini)
{
	int	i;
	int	j;
	int	qts;

	i = 0;
	while (mini->export.tab[i])
	{
		qts = 1;
		j = 0;
		ft_putstr_fd("declare -x ", 1);
		while (mini->export.tab[i][j])
		{
			ft_putchar_fd(mini->export.tab[i][j], 1);
			if (mini->export.tab[i][j] == '=' && qts)
			{
				ft_putchar_fd('"', 1);
				qts--;
			}
			j++;
		}
		if (!qts)
			ft_putchar_fd('"', 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
}

void	sort_env(t_mini *mini)
{
	char	**c_env;
	char	*tmp;
	int		i;
	int		j;

	c_env = copy_env(mini);
	i = 0;
	while (c_env[i])
	{
		j = i + 1;
		while (c_env[j])
		{
			if (ft_strcmp(c_env[i], c_env[j]) > 0)
			{
				tmp = c_env[i];
				c_env[i] = c_env[j];
				c_env[j] = tmp;
			}
			j++;
		}
		i++;
	}
	export_print(mini);
}

void	export_go(t_mini *mini,int i)
{
	printf("%s\n",ft_strchr(mini->echo[i],'='));
}
void	check_args(t_mini *mini)
{
	int i;
	
	i = 1;
	while (mini->echo[i] && mini->echo[i][0] != '=')
	{
		if(ft_isalpha(mini->echo[i][0]) || mini->echo[i][0] == '_')
			export_go(mini,i);
		else
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(mini->echo[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
		}
		i++;
	}
}
void	export_cmd(t_mini *mini)
{
	if (!mini->echo[1])
	{		
		sort_env(mini);
	}
	else
	{
		check_args(mini);
	}
}
