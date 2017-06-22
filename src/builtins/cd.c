
#include "minishell.h"

char	*retrieve_home(char **env)
{
	int i;
	char *home;
	char *envvar;

	i = 0;
	home = NULL;
	while (env[i])
	{
		envvar = NULL;
		if (ft_strlen(env[i]) >= 5)
			envvar = ft_strsub(env[i], 0, 5);
		if (ft_strequ(envvar, "HOME="))
		{
			home = ft_strsub(env[i], 5, ft_strlen(env[i]) - 5);
			free(envvar);
			break ;
		}
		if (envvar)
			free(envvar);
		i++;
	}
	return (home);
}

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
	return (path);
}

int		get_env_pos(char **env, char *var)
{
	int		i;
	int		j;

	i = 0;
	while(env[i])
	{
		j = 0;
		while (var[j] == env[i][j])
			j++;
		if (var[j] == '\0')
			return (i);
		i++;
	}
	return (-1);
}

void update_cwd_vars(char *cwd, char **env, char *envvar)
{
	int		pos;

	pos = get_env_pos(env, envvar);
	if (pos < 0)
		return ;
	free(env[pos]);
	env[pos] = ft_strjoin(envvar, cwd);
}

void	get_cd_error(char *arg)
{
	struct stat path_stat;

    lstat(arg, &path_stat);
    if (S_ISREG(path_stat.st_mode))
		print_errors(CD_NOT_A_DIR, arg);
	else if (S_ISDIR(path_stat.st_mode))
		print_errors(CD_NO_RIGHTS, arg);
	else
		print_errors(DIR_NOT_FOUND, arg);
}

void	builtins_cd(char **argv, char **env)
{
	char	*cwd;
	char	*path;

	cwd = NULL;
	path = get_path(argv, env);
	int i;
	i = 0;
	cwd = getcwd(cwd, MAX_PATH);
	i = chdir(path);
	if (!i)
	{
		update_cwd_vars(cwd, env, "OLDPWD=");
		free(cwd);
		cwd = NULL;
		cwd = getcwd(cwd, MAX_PATH);
		update_cwd_vars(cwd, env, "PWD="); // make this. update the env variale for current working directory
	}
	else
		get_cd_error(argv[0]); // make me. check if the argument is an existing file.
	if (path)
		free(path);
	if (cwd)
		free(cwd);
}
