#include "minishell.h"
int main(int ac, char **av, char **env)
{
	int i;
	char *line;
	char **paths;
	char	**cmd1;
	char	*path1;
	char **echo;
	int		status;

	(void)av;
	(void)env;
	if (ac > 1)
		return(0);
	i = 0;
	line = readline("Minishell$ ");
	while (line)
	{
		if (*line)
			add_history(line);
		if (!ft_strncmp(line, "exit", 4))
		{
			write (1, "exit\n", 5); 
			return (0);
		}   
		if (!ft_strncmp(line, "pwd", 3))
			pwd_cmd();
		if(!ft_strncmp(line, "echo",4))
		{
			echo = ft_split(line,' ');
			echo_cmd(echo);
		}
		// if(!ft_strncmp(line, "cd",2 ))
		// 	cd_cmd("/Users/imabid/Desktop/Minishell/libft");
		else
		{
			int pid = fork();
			if(pid == 0)
			{
				paths = ft_split(find_path(env), ':');
				cmd1 = ft_split(line, ' ');
				path1 = get_path(paths, cmd1);
				if(execve(path1,cmd1,env) == -1)
					perror("n_execve\n");
			}
		}
		wait(&status);
		line =  readline("Minishell$ ");
		// runcmd(parsing(line));
	}
	return (0);
}