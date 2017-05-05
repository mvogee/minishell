
#include "minishell.h"

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
