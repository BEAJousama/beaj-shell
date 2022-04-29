#include "minishell.h"

extern t_glob glob;

static int    venv_count(t_venv *venv)
{
    int    counter;

    counter = 0;
    while (venv)
    {
        counter++;
        venv = venv->next;
    }
    return (counter);
}

char    **venv_export_array(t_venv    *venv)
{
    int        i;
    int        len;
    char    *str;
    char    **env;

    i = 0;
    len = venv_count(venv);
    env = malloc(sizeof(char *) * (len + 1));
    while (venv && i < len)
    {    
        str = ft_strjoin(venv->key, "=");
        str = ft_strjoin(str, venv->value);
        env[len - i++ - 1] = str;
		venv = venv->next;
    }
    env[len] = NULL;
    return (env);
}

int   ft_execve(char **cmd)
{
    char    *path;
    char    **env;
    int        pid;

    env = venv_export_array(*glob.venv);
    path = get_path(*cmd);
    pid = fork();
    if (pid == -1)
        return (-2);
    else if (pid == 0)
    {
        if (execve(path, cmd, env) == -1)
            return (-1);
    }
    wait(&glob.status);
    return (0);
}

void	shlvl_add(t_m *m)
{
	char *val;

	m->shlvl = ft_atoi(get_venv("SHLVL",glob.venv));
	m->shlvl++;
	val = ft_itoa(m->shlvl);
	add_global_venv("SHLVL",val,glob.venv);
	add_global_venv("SHLVL",val,glob.ennv);

}
void	lets_start(char **env)
{
	glob.venv = set_global_env(env, glob.venv);
	glob.ennv = set_global_env(env, glob.ennv);
}

int main(int ac, char **av, char **env)
{
	t_m m;

	(void)av;
	(void)env;
	if (ac > 1)
		return(0);
	m.i = 0;
	lets_start(env);
	shlvl_add(&m);
	m.line = readline("minishell$ ");
	while (m.line)
	{
		if (*m.line)
			add_history(m.line);
		if (!ft_strncmp(m.line, "exit", 4))
		{
			write (1, "exit\n", 5); 
			return (0);
		}   
		else if (!ft_strncmp(m.line, "pwd", 3))
			pwd_cmd();
		else if (!ft_strncmp(m.line, "env", 3))
		{
			m.args = ft_split(m.line,' ');
			env_cmd(m.args);
		}
		else if (!ft_strncmp(m.line, "cd", 2))
		{
			m.args = ft_split(m.line,' ');
			cd_cmd(m.args);
		}
		else if (!ft_strncmp(m.line, "export", 6))
		{
			m.echo = ft_split(m.line,' ');
			export_cmd(m.echo);
		}
		else if(!ft_strncmp(m.line, "echo",4))
		{
			m.echo = ft_split(m.line,' ');
			echo_cmd(m.echo);
		}
		else if(!ft_strncmp(m.line, "exit",4))
		{
			m.args = ft_split(m.line,' ');
			exit_cmd(&m);
		}
		else if(!ft_strncmp(m.line, "unset",4))
		{
			m.args = ft_split(m.line,' ');
			unset_cmd(m.args);
		}
		else
		{
			m.cmd1 = ft_split(m.line, ' ');
			ft_execve(m.cmd1);
		}
		// printf("%d\n",glob.status);
		m.line =  readline("minishell$ ");
	}
	return (0);
}