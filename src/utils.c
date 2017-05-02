
#include "minishell.h"

int	count_words(char const *s, char c, int flag, int wrdstrt)
{
	int word_count;
	int index;

	word_count = 0;
	index = 0;
	if (!*s)
		return (0);
	if (s[0] != c)
	{
		word_count++;
		if (flag == 1 && wrdstrt == 1)
			return (index);
	}
	while (s[index])
	{
		if (s[index] == c && s[index + 1] != c && s[index + 1] != '\0')
			word_count++;
		index++;
		if (flag == 1 && word_count == wrdstrt)
			return (index);
	}
	return (word_count);
}
