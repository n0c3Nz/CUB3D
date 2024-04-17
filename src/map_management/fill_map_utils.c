/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guortun- <guortun-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:09:03 by guortun-          #+#    #+#             */
/*   Updated: 2024/04/10 14:17:56 by guortun-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CUB3D.h"

int	find_long_line(char *buffer)
{
	int i;
	int prev_chars;
	int chars;

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
	return prev_chars;
}

char	**allocate_memory(t_cub *cub, int lines)
{
    char **mold = malloc(sizeof(char *) * lines);
    if (!mold)
        error_msg("Error: malloc()\n", cub);
    return mold;
}

int checkBufferAndFillLines(char buffer_k, char *lines_ij, int *j)
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