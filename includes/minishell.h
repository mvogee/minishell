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

#endif
