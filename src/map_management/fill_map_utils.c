/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guortun- <guortun-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:09:03 by guortun-          #+#    #+#             */
/*   Updated: 2024/05/15 10:46:13 by guortun-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CUB3D.h"

int	find_long_line(char *buffer)
{
	int	i;
	int	prev_chars;
	int	chars;

	chars = 0;
	prev_chars = 0;
	i = 0;
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
		{
			if (chars > prev_chars)
				prev_chars = chars;
			chars = 0;
		}
		else
			chars++;
		i++;
	}
	return (prev_chars);
}

char	**allocate_memory(int lines)
{
	char	**mold;

	mold = malloc(sizeof(char *) * lines);
	if (!mold)
		return (NULL);
	return (mold);
}

int	check_bff_and_fill_lines(char buffer_k, char *lines_ij, int *j)
{
	if (buffer_k == 'N' || buffer_k == 'S' || buffer_k == 'W'
		|| buffer_k == 'E')
	{
		*lines_ij = '0';
		(*j)++;
		return (1);
	}
	else if (buffer_k == ' ')
	{
		*lines_ij = '1';
		(*j)++;
		return (1);
	}
	else if (buffer_k != '\n')
	{
		*lines_ij = buffer_k;
		(*j)++;
		return (1);
	}
	return (0);
}
