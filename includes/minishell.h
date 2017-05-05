#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft.h"
#include "ft_printf.h"
#include <stdlib.h>

extern char **environ;

enum e_errors
{
	NO_CLOSING_QUOTE,
	WRONG
};

typedef struct	s_environ
{
	char	*curdir;

}				t_environ;

int	count_words(char const *s, char c, int flag, int wrdstrt);

/*
** main.c
*/

int		print_errors(int error);

/*
** argv_help.c
*/

int		count_arguments(char *line);
char	*get_argline(void);
int		find_arglen(char *line);
char	*remove_inside_quotes(char *line);
char	*abstract_arg(int arglen, char *line);

/*
** builtins
*/

void	builtins_echo(int argc, char **argv);

#endif
