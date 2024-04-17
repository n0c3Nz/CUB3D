/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guortun- <guortun-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:43:03 by guortun-          #+#    #+#             */
/*   Updated: 2024/04/10 14:15:18 by guortun-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CUB3D.h"

static void	initializeindices(int *i, int *j, int *k)
{
	*i = 0;
	*j = 0;
	*k = 0;
}

static void	allocatememoryforline(char **lines_i, int line_length, t_cub *cub)
{
	*lines_i = malloc(sizeof(char) * line_length + 1);
	if (!*lines_i)
		error_msg("Error: malloc()\n", cub);
}

static void	fill_linewithones(char *lines_i, int line_length)
{
	int	j;

	j = 0;
	while (j < line_length)
		lines_i[j++] = '1';
	lines_i[j] = '\0';
}

void	fill_mold(t_cub *cub, char **lines, char *buffer, int line_length)
{
	int	i;
	int	j;
	int	k;

	initializeindices(&i, &j, &k);
	allocatememoryforline(&lines[i], line_length, cub);
	while (buffer[k])
	{
		if (!checkBufferAndFillLines(buffer[k], &lines[i][j], &j))
		{
			while (j < line_length)
				lines[i][j++] = '1';
			lines[i][j] = '\0';
			if (buffer[k + 1])
			{
				i++;
				lines[i] = malloc(sizeof(char) * line_length + 1);
				if (!lines[i])
					error_msg("Error: malloc()\n", cub);
				j = 0;
			}
		}
		k++;
	}
	fill_linewithones(lines[i], line_length);
}

void	fill_map(t_cub *cub, char *buffer)
{
	int	line_length;

	while (*buffer != '\0')
	{
		if (*buffer != '\n' && (*(buffer + 1) != '\0'))
			buffer++;
		else if (*buffer == '\n' && (*(buffer + 1) != '\0'))
		{
			buffer++;
			if (*buffer == '1' || *buffer == ' ')
				break ;
		}
	}
	line_length = find_long_line(buffer);
	cub->map.lines = allocate_memory(cub, cub->map.map_size);
	if (!cub->map.lines)
		error_msg("Error: malloc()\n", cub);
	fill_mold(cub, cub->map.lines, buffer, line_length);
}
