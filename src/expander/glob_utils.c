#include "minishell.h"

t_glob	glob = {.venv = NULL, .vars = NULL, .status = 0};

void	set_global_env(char **env)
{
	int		len;
	t_venv	*new;
	
	glob.venv = init_venv(glob.venv);
	glob.vars = init_venv(glob.vars);
	len = 0;
	while (*(env + len))
	{
		new = new_venv(get_key(*(env + len)), get_value(*(env + len)));
		venv_add_back(glob.venv, new);
		len++;
	}
}

void	add_global_vars(char *key, char *value)
{
	int		len;
	t_venv	*var;

	len = 0;
	var = new_venv(key, value);
	venv_add_back(glob.vars, var);
}

void	add_global_venv(char *key, char *value)
{
	int		len;
	t_venv	*venv;

	len = 0;
	venv = new_venv(key, value);
	venv_add_back(glob.venv, venv);
}

char	*get_venv(char *key)
{
	t_venv	*venv;

	venv = *glob.venv;
	while (venv)
	{
		if (!ft_strcmp(venv -> key, key))
			return (venv -> value);
		venv = venv -> next;
	}
	return (NULL);
}

char	*get_var(char *key)
{
	t_venv	*var;

	var = *glob.vars;
	while (var)
	{
		if (!ft_strcmp(var -> key, key))
			return (var -> value);
		var = var -> next;
	}
	return (NULL);
}