
#include "minishell.h"

void	pwd(void)
{
	char *pwd;

	pwd = NULL;
	pwd = getcwd(pwd, MAX_PATH);
	if (pwd)
	{
		ft_printf("%s\n", pwd);
		free(pwd);
	}
	else
		ft_printf("something went horribly wrong getting your directory!");
}
