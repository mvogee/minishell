
#include "minishell.h"

// • You must implement a series of builtins: echo, cd, setenv, unsetenv, env, exit

int run_minishell_command(int argc, char **argv, char **env)
{
	if (ft_strequ(argv[0], "exit"))
		return (0);
	else if (ft_strequ(argv[0], "echo"))
		builtins_echo(argc, argv);
	else if (ft_strequ(argv[0], "cd")) // deal with cd being invoked when /dir is given without cd previosuly
		builtins_cd(argc, argv, env); // make this
	// else if (ft_strequ(argv[0], "setenv"))
	// 	builtins_setenv(argv, argc); // make this
	// else if (ft_strequ(argv[0], "unsetenv"))
	// 	builtins_unsetenv(argv, argc); // make this
	// else if (ft_strequ(argv[0], "env"))
		// builtins_env(argv, argc, env); // make this
	// else if (ft_strequ(argv[0], "pwd"))
	// 	builtins_pwd(argv, argc); // make this. bonus
	// else if (argv[0][0] == '.' && argv[0][1] == '/')
	// 	run_executable(argv, argc); // make this.
	else
		not_builtin(argv, env); // make this. searches the env paths for the executable
//		ft_printf("command not found: %s\n", argv[0]);
	return (1);

}

// char	**get_commands(char *line)
// {
	// int		i;
	// char	*command;
	// char	**commands;
	//
	// i = 0;
	// commands = NULL;
	// while (line)
	// {
	// 	while (line[i] && line[i] != ' ' && line[i] != '\"')
	// 		i++;
	// 	if (line[i] == '\"')
	// 	{
	// 		if ((i = find_closing_quote(line, i)) == -1); // make this
	// 			return (NULL);
	// 		command = ft_strsub(line, i);
	// 		add_command();
	// 	}
	// 	else if (line[i] == ' ')
	// 		add_command();
	// 	line += i;
	// 	i = 0;
	// }
	// return (commands);
// }

// char	**get_args(char *line, int argc)
// {
// 	char **args;
// }

int		print_errors(int error, char *problem)
{
	if (error == NO_CLOSING_QUOTE)
		ft_printf("missing closing quote\n");
	else if (error == DIR_NOT_FOUND)
		ft_printf("no directory \"%s\" found\n", problem);
	else if (error == COMMAND_NOT_FOUND)
		ft_printf("command \"%s\" not found\n", problem);
	return (0);
}

char	**get_argv(char *line, int argc)
{
	char 	**argv;
	int		i;
	int		arglen;

	i = 0;
	argv = (char**)ft_memalloc(sizeof(char*) * argc + 1);
	if (!argv)
		return (NULL);
	while (line && i <= argc && *line)
	{
		arglen = find_arglen(line);
		argv[i] = abstract_arg(arglen, line);
		line += arglen;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

int		minishell(t_environ *env)
{
	char	*line;
	int		running;

	line = NULL;
	running = 1;
	while (running)
	{
		write(1, "$> ", 3);
		line = get_argline();
		env->argc = count_arguments(line);
		if (env->argc > 0)
		{
			env->argv = get_argv(line, env->argc);
			running = run_minishell_command(env->argc, env->argv, env->env); // working on these
		//	free_argv(env->argv, env->argc); // make this
			free(line);
		}
		line = NULL;
	}
	return (1);
}

int		main(int argc, char **argv, char **envp)
{
	t_environ	environ; // may not even need this actually

	environ.curdir = (char*)ft_memalloc(sizeof(char) * 1024);
	environ.curdir = getcwd(environ.curdir, 1024);
	environ.env = ft_dup_tbl(envp);
	(void)argc;
	(void)argv;
	minishell(&environ);
	exit(EXIT_SUCCESS);
}
