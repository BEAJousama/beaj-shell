#include "minishell.h"

extern t_glob glob;

int	env_copy(t_mini *mini, char **env)
{
	int i;
	i = 0;
	while (env[i])
		i++;
	if (!(mini->env_g = (char **)malloc(sizeof(char *) * (i + 1))))
		return (0);
	i = 0;
	while (env[i])
	{
		mini->env_g[i] = ft_strdup(env[i]);
		i++;
	}
	return 1;
}
int main(int ac, char **av, char **env)
{
	t_mini mini;

	(void)av;
	(void)env;
	if (ac > 1)
		return(0);
	mini.i = 0;
	env_copy(&mini,env);
	glob.venv = set_global_env(env, glob.venv);
	glob.ennv = set_global_env(env, glob.ennv);
	// set_global_env(env, glob.ennv);
	mini.line = readline("minishell$ ");
	while (mini.line)
	{
		if (*mini.line)
			add_history(mini.line);
		if (!ft_strncmp(mini.line, "exit", 4))
		{
			write (1, "exit\n", 5); 
			return (0);
		}   
		else if (!ft_strncmp(mini.line, "pwd", 3))
			pwd_cmd();
		else if (!ft_strncmp(mini.line, "env", 3))
		{
			mini.args = ft_split(mini.line,' ');
			env_cmd(&mini);
		}
		else if (!ft_strncmp(mini.line, "cd", 2))
		{
			mini.args = ft_split(mini.line,' ');
			cd_cmd(&mini);
		}
		else if (!ft_strncmp(mini.line, "export", 6))
		{
			mini.echo = ft_split(mini.line,' ');
			export_cmd(&mini);
		}
		else if(!ft_strncmp(mini.line, "echo",4))
		{
			mini.echo = ft_split(mini.line,' ');
			echo_cmd(mini.echo);
		}
		else if(!ft_strncmp(mini.line, "unset",4))
		{
			mini.args = ft_split(mini.line,' ');
			unset_cmd(&mini);
		}
		else
		{
			int pid = fork();
			if(pid == 0)
			{
				mini.paths = ft_split(find_path(mini.env_g), ':');
				mini.cmd1 = ft_split(mini.line, ' ');
				mini.path1 = get_path(mini.paths, mini.cmd1);
				// if(execve(mini.path1,mini.cmd1,mini.env) == -1)
				// 	perror("n_execve\n");
				execve(mini.path1,mini.cmd1,mini.env);
			}
		}
		wait(&mini.status);
		mini.line =  readline("minishell$ ");
	}
	while(1);
	return (0);
}