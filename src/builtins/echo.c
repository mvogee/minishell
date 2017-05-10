
#include "minishell.h"

void	builtins_echo(int argc, char **argv)
{
	int i;

	i = 1;
	while (i < argc)
	{
		ft_printf("%s", argv[i]);
		i++;
		if (i < argc)
			write(1, " ", 1);
	}
	printf("\n");
}
