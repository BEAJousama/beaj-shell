#include "minishell.h"

extern t_glob glob;

int	env_copy(t_m *m, char **env)
{
	int i;
	i = 0;
	while (env[i])
		i++;
	if (!(m->env_g = (char **)malloc(sizeof(char *) * (i + 1))))
		return (0);
	i = 0;
	while (env[i])
	{
		m->env_g[i] = ft_strdup(env[i]);
		i++;
	}
	return 1;
}
int main(int ac, char **av, char **env)
{
	t_m m;

	(void)av;
	(void)env;
	if (ac > 1)
		return(0);
	m.i = 0;
	env_copy(&m,env);
	glob.venv = set_global_env(env, glob.venv);
	glob.ennv = set_global_env(env, glob.ennv);
	// set_global_env(env, glob.ennv);
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
			env_cmd(&m);
		}
		else if (!ft_strncmp(m.line, "cd", 2))
		{
			m.args = ft_split(m.line,' ');
			cd_cmd(&m);
		}
		else if (!ft_strncmp(m.line, "export", 6))
		{
			m.echo = ft_split(m.line,' ');
			export_cmd(&m);
		}
		else if(!ft_strncmp(m.line, "echo",4))
		{
			m.echo = ft_split(m.line,' ');
			echo_cmd(m.echo);
		}
		else if(!ft_strncmp(m.line, "unset",4))
		{
			m.args = ft_split(m.line,' ');
			unset_cmd(&m);
		}
		else
		{
			int pid = fork();
			if(pid == 0)
			{
				m.paths = ft_split(find_path(m.env_g), ':');
				m.cmd1 = ft_split(m.line, ' ');
				m.path1 = get_path(m.paths, m.cmd1);
				// if(execve(m.path1,m.cmd1,m.env) == -1)
				// 	perror("n_execve\n");
				execve(m.path1,m.cmd1,m.env);
			}
		}
		wait(&m.status);
		m.line =  readline("minishell$ ");
	}
	while(1);
	return (0);
}