
#include "minishell.h"

void	not_builtin(int argc, char **argv, char **env)
{
	char *path;

	path = look_for_executable(argv[0]); // make this
	if (!path)
		print_errors(COMMAND_NOT_FOUND);
	pid_t	child_pid;
	int		status;
	pid_t	pid;

	child_pid = fork();
	if (child_pid == 0)
	{
		execv(path, argv++, env);
		printf("why?\n"); 
	}
}
