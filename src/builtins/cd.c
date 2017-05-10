
#include "minishell.h"

void	builtins_cd(int argc, char **argv, char **env)
{
	char *cwd;

	cwd = NULL;
	int i;
	i = 0;
	cwd = getcwd(cwd, MAX_PATH);
	if (argc < 2 || ft_strequ(argv[1], "~") || ft_strequ(argv[1], "/~"))
		chdir("/users/mvogee");
	//	get_home_dir(env) // retrieve the home directory from the env
	else
		i = chdir(argv[1]);
	printf("%d\n", i);
	if (!i)
	{
		printf("%s\n", cwd);
//		update_old_cwd(cwd, env); // make this. update the env variable for last_pwd
		free(cwd);
		cwd = NULL;
		cwd = getcwd(cwd, MAX_PATH);
		printf("%s\n", cwd);
//		update_cwd(cwd, env); // make this. update the env variale for current working directory
	}
	else
		print_errors(DIR_NOT_FOUND);
	free(cwd);
	printf("%s\n", env[18]);
	printf("%s\n", env[19]);
}
