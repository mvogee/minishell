#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft.h"
#include "ft_printf.h"
#include <signal.h>
#include <stdlib.h>

extern char **environ;
# define MAX_PATH 1024

enum e_errors
{
	NO_CLOSING_QUOTE,
	DIR_NOT_FOUND,
	COMMAND_NOT_FOUND,
	WRONG
};

typedef struct	s_environ
{
	char	*curdir; //dont know that i need to hold this
	char	**env;
	char	**argv;
	int		argc;
}				t_environ;

int	count_words(char const *s, char c, int flag, int wrdstrt);

/*
** main.c
*/

int		print_errors(int error, char *problem);

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

void	builtins_cd(char **argv, char **env);

void	not_builtin(char **argv, char **env);

#endif
