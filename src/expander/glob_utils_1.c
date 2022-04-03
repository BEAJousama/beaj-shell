#include "minishell.h"

char	*get_key(char *env)
{
	int	len;

	len = 0;
	while (env[len] && env[len] != '=')
		len++;
	return (ft_strndup(env, len + 1));
}

char	*get_value(char *env)
{
	int	len;

	len = 0;
	while (env[len] && env[len] != '=')
		len++;
	return (ft_strdup(env + len + 1));
}

t_venv	**init_venv(t_venv **venv)
{
	venv = malloc(sizeof(t_venv *));
	if (!venv)
		return (NULL);
	*venv = NULL;
	return (venv);
}

t_venv	*new_venv(char *key, char *value)
{
	t_venv	*venv;
	
	venv = malloc(sizeof(t_venv) * 1);
	venv -> key = ft_strdup(key);
	venv -> value = ft_strdup(value);
	venv -> next = NULL; 
	return (venv);
}

void	venv_add_back(t_venv **venv, t_venv *new)
{
	t_venv	*first;

	if (!venv)
		return ;
	if (!*venv)
		*venv = new;
	else
	{
		first = *venv;
		while (first -> next != NULL)
			first = first -> next;
		first -> next = new;
	}
}