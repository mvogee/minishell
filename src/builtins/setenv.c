
#include "minishell.h"

int		builtins_setenv(int argc, char **argv, char **env)
{
	const char *value;
	const char *name;

	if (argc < 2 || !env || !argv)
		return (0);
	name = argv[1];
	if (argc > 2)
		value = argv[2];
	else
		value = NULL;
	ft_printf("entered setenv\nYou are wanting to add: %s to the env?\nWell TOO BAD i havn't finished coding it yet.\n", argv[1]);
	(void)env;
	return (1);
}
