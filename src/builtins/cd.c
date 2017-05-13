
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

// int		chdir_home(char **env)
// {
// 	int ret;
// 	char *home_dir;
//
// 	ret = -1;
// 	home_dir = retrieve_home(env);
// 	if (home_dir)
// 	{
// 		ret = chdir(home_dir);
// 		free(home_dir);
// 	}
// 	return (ret);
// }

char *get_path(char **argv, char **env)
{
	char	*path;
	char	*homedir;

	path = NULL;
	homedir = NULL;
	if (!(*argv) || argv[0][0] == '~')
		homedir = retrieve_home(env);
	if (homedir && *argv)
		path = ft_strjoin(homedir, ((*argv) + 1));
	else if (*argv)
		path = ft_strdup(*argv);
	else
		path = ft_strdup(homedir);
	if (homedir)
		free(homedir);
	printf("%s\n", path);
	return (path);
}

int		get_oldpwd_pos(char **env)
{
	int		i;

	i = 0;
	while(env[i])
	{
		if (env[i][0] == 'O' && env[i][1] == 'L' && env[i][2] == 'D' &&
			env[i][3] == 'P' && env[i][4] == 'W' &&
			env[i][5] == 'D' && env[i][6] == '=')
		return (i);
		i++;
	}
	return (-1);
}

void	update_old_cwd(char *cwd, char **env)
{
	char	*envvar;
	int		pos;

	envvar = "OLDPWD=";
	pos = get_oldpwd_pos(env);
	if (pos < 0)
		return ;
	free(env[pos]);
	env[pos] = ft_strjoin(envvar, cwd);
}

// catch for being an existing file but not directory. currently just throws normal error.
// need to rethink this functions functionality and how to have it work.
void	builtins_cd(char **argv, char **env)
{
	char	*cwd;
	char	*path;

	cwd = NULL;
	path = get_path(argv, env);
	printf("%s\n", path);
	int i;
	i = 0;
	cwd = getcwd(cwd, MAX_PATH);
	i = chdir(path);
//	printf("%d\n", i);
	if (!i)
	{
		printf("%s\n", cwd);
		update_old_cwd(cwd, env); // make this. update the env variable for last_pwd
		free(cwd);
		cwd = NULL;
		cwd = getcwd(cwd, MAX_PATH);
		printf("%s\n", cwd);
	//	update_cwd(cwd, env); // make this. update the env variale for current working directory
	}
	else
		print_errors(DIR_NOT_FOUND, argv[0]);
	if (path)
		free(path);
	if (cwd)
		free(cwd);
	printf("%s\n", env[18]);
	printf("%s\n", env[19]);
}
