
#include "minishell.h"

char	*retrieve_home(char **env)
{
	int i;
	char *home;

	i = 0;
	home = NULL;
	while (env[i])
	{
		if (env[i][0] == 'H' && env[i][1] == 'O' && env[i][2] == 'M' && env[i][3] == 'E' && env[i][4] == '=')
		{
			home = ft_strsub(env[i], 5, ft_strlen(env[i]) - 5);
			break ;
		}
		i++;
	}
	return (home);
}

int		chdir_home(char **env)
{
	int ret;
	char *home_dir;

	ret = -1;
	home_dir = retrieve_home(env);
	if (home_dir)
	{
		ret = chdir(home_dir);
		free(home_dir);
	}
	return (ret);
}

void	builtins_cd(int argc, char **argv, char **env)
{
	(void)argc; // might just take out argc;
	char *cwd;

	cwd = NULL;
	int i;
	i = 0;
	cwd = getcwd(cwd, MAX_PATH);
	if (ft_strequ(argv[0], "~") || (argv[1] && ft_strequ(argv[1], "~")))
		i = chdir_home(env);
	else
		i = chdir(argv[0]);
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
		print_errors(DIR_NOT_FOUND, argv[0]);
	free(cwd);
	printf("%s\n", env[18]);
	printf("%s\n", env[19]);
}
