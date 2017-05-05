
#include "minishell.h"

void	builtins_echo(int argc, char **argv)
{
	int i;
	int nflag;

	i = 1;
	nflag = 0;
	if (ft_strequ(argv[1], "-n"))
	{
		nflag = 1;
		i++;
	}
	while (i < argc)
	{
		ft_printf("%s", argv[i]);
		i++;
		if (i < argc)
			write(1, " ", 1);
	}
	if (!nflag)
		printf("\n");
}
