/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup_tbl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvogee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/30 18:54:13 by mvogee            #+#    #+#             */
/*   Updated: 2016/10/30 19:47:18 by mvogee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_dup_tbl(char **tbl)
{
	char	**dup;
	int		size;
	int		i;

	i = 0;
	size = 0;
	while(tbl[size])
		size++;
	dup = (char**)ft_memalloc(sizeof(char*) * size + 1);
	if (!dup)
		return (NULL);
	while (i < size)
	{
		dup[i] = ft_strdup(tbl[i]);
		i++;
	}
	dup[i] = NULL;
	return (dup);
}
