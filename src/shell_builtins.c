
#include "minishell.h"

int		find_paths(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (env[i][0] == 'P' && env[i][1] == 'A' && env[i][2] == 'T' && env[i][3] == 'H' && env[i][4] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int		try_to_execute(char **paths, char *path, char **argv, char **env)
{
	int		i;
	int		runstatus;
	char	*slash;
	char	*trypath;

	i = 0;
	runstatus = -1;
	slash = NULL;
	trypath = NULL;
	if (path && !(path[0] == '/'))
		slash = ft_strjoin("/", path);
	while (paths[i] && runstatus < 0)
	{
		trypath = (slash ?
			ft_strjoin(paths[i], slash) : ft_strjoin(paths[i], path));
		runstatus = execve(trypath, argv, env);
		ft_strdel(&trypath);
		i++;
	}
	if (slash)
		free(slash);
	if (trypath)
		free(trypath);
	return (runstatus);
}

void	free_paths(char ***paths)
{
	int i;

	i = 0;
	if (!(*paths))
		return ;
	while ((*paths)[i])
	{
		free((*paths)[i]);
		i++;
	}
	free(*paths);
}

int		ft_execvep(char *path, char **argv, char **env)
{
	char	**paths;
	int		pathnum;
	int		runstatus;

	runstatus = -1;
	paths = NULL;
	pathnum = find_paths(env);
	if (pathnum < 0)
		return (-1);
	paths = ft_strsplit(env[pathnum] + 5, ':');
	if (!paths)
		return (-1);
	runstatus = try_to_execute(paths, path, argv, env);
	free_paths(&paths);
	return (runstatus);
}

void	not_builtin(char **argv, char **env)
{
	int		executed;
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		executed = ft_execvep(argv[0], argv, env);
		if (executed < 0)
		{
			print_errors(COMMAND_NOT_FOUND, argv[0]);
			exit(EXIT_FAILURE); // need this to actually break out of the child precess;
		}
	}
	else if (pid < 0)
		ft_printf("%s\n", "what the fork! fork failed!\n");
	else
	{
		waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status)) // not sure what these do
			waitpid(pid, &status, WUNTRACED);
		kill(pid, SIGCONT);
	}
}
