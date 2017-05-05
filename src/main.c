
#include "minishell.h"

// • You must implement a series of builtins: echo, cd, setenv, unsetenv, env, exit

// int run_minishell_command(int argc, char **argv)
// { // 100% sure i will need a struct to keep track of curent directory and other things
// 	if (ft_strequ(argv[0], "exit")
// 		return (0);
// 	else if (ft_strqu(argv[0], "echo"))
// 		builtins_echo(argv, argc); // make this
// 	else if (ft_strequ(argv[0], "cd"))
// 		builtins_cd(argv, argc); // make this
// 	else if (ft_strequ(argv[0], "setenv"))
// 		builtins_setenv(argv, argc); // make this
// 	else if (ft_strequ(argv[0], "unsetenv"))
// 		builtins_unsetenv(argv, argc); // make this
// 	else if (ft_strequ(argv[0], "env"))
// 		builtins_env(argv, argc); // make this
// 	else if (ft_strequ(argv[0], "pwd"))
// 		builtins_pwd(argv, argc); // make this. bonus
// 	else if (argv[0][0] == '.' && argv[0][1] == '/')
// 		run_executable(argv, argc); // make this.
// 	else
// 		ft_printf("command not found: %s\n", argv[0]);
//
// }

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

int		print_errors(int error)
{
	if (error == NO_CLOSING_QUOTE)
		ft_printf("missing closing quote\n");
	return (0);
}

int		count_arguments(char *line)
{
	int		count;

	count = ((!line || *line == '\0') ? 0 : 1);
	while (line && *line)
	{
		if (*line == '\"')
		{
			line++;
			while (*line && *line != '\"')
				line++;
			if (*line == '\0')
				return (print_errors(NO_CLOSING_QUOTE));
			line++;
		}
		else if (*line == ' ' || *line == '\t')
		{
			while (*line && *line == ' ')
				line++;
			count += (*line == '\0' ? 0 : 1);
		}
		else
			line++;
	}
	return (count);
}

char	*get_argline(void)
{
	char 	*line;
	char	*trimmed;

	trimmed = NULL;
	line = NULL;
	get_next_line(0, &line);
	trimmed = ft_strtrim(line);
	free(line);
	if (!trimmed || *trimmed == '\0')
		return (NULL);
	return (trimmed);
}

int		find_arglen(char *line)
{
	int		i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	while (line[i])
	{
		if (line[i] == '\"')
		{
			i++;
			while (line[i] && line[i] != '\"')
				i++;
		}
		if (line[i] == ' ' || line[i] == '\t')
			break;
		i++;
	}
	return (i);
}

char	*remove_inside_quotes(char *line)
{
	int		i;
	char	*sub;
	char	*remain;
	char 	*ret;

	i = 0;
	ret = ft_strdup(line);
	while (ret[i])
	{
		if (ret[i] == '\"')
		{
			sub = ft_strsub(ret, 0, i);
			ret += i;
			remain = ft_strdup(ret + 1);
			ret -= i;
			free(ret);
			ret = ft_strjoin(sub, remain);
			free(sub);
			free(remain);
			i = 0;
		}
		i++;
	}
	return (ret);
}

char	*abstract_arg(int arglen, char *line)
{
	char	*arg;
	char	*first;

	while (*line == ' ' || *line == '\t' || *line == '\"')
	{
		line++;
		arglen--;
	}
	if (line[arglen - 1] == ' ' || line[arglen - 1] == '\t' || line[arglen - 1] == '\"')
	{
		printf("triggerd\n");
		arglen--;
	}
	first = ft_strsub(line, 0, arglen);
	if (!first)
		return (NULL);
	arg = remove_inside_quotes(first);
	free(first);
	return (arg);
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
		arglen = find_arglen(line); // make this. return int that is length of the entire argument
		printf("%d\n", arglen);
		argv[i] = abstract_arg(arglen, line); // make this. if there are quotes it needs to remove them
		printf("argv[%d]: %s\n", i, argv[i]);
		line += arglen;
		i++;
	}
	argv[i] = NULL;
	for (int k = 0; k < argc; k++)
		printf("argv[%d]: %s\n", k, argv[k]);
	return (argv);
}

int		minishell(char **envp)
{
	(void)envp;
	char	*line;
	char	**argv;
	int		argc;
	int		running;

	line = NULL;
	running = 1;
	while (running)
	{
		ft_printf("$>");
		line = get_argline();
		argc = count_arguments(line);
		printf("argc: %d\n", argc); // remove me
		if (argc > 0)
		{
			argv = get_argv(line, argc); // make this. splits up the line by quotes and spaces
			ft_printf("\ngreater than 0\n");
			for (int i = 0; i < argc; i++)
				printf("argv[%d]: %s\n", i, argv[i]);
		//	running = run_minishell_command(argc, argv));
		//	free_argv(argv, argc); // make this
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
	(void)argc;
	(void)argv;
	minishell(envp);
	exit(EXIT_SUCCESS);
}
