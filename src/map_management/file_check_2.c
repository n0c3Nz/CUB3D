/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guortun- <guortun-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:19:29 by guortun-          #+#    #+#             */
/*   Updated: 2024/04/08 11:24:57 by guortun-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CUB3D.h"

static int	calc_lines(char *buffer)
{
	int	i;
	int	lines;

	i = 0;
	lines = 0;
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
			lines++;
		i++;
	}
	return (lines);
}

static void	cpy_and_incr(char *line, char *buffer, int *i, int *j)
{
	line[*j] = buffer[*i];
	(*j)++;
}

static void	init_values(int *i, int *j, int *k)
{
	*i = 0;
	*j = 0;
	*k = 0;
}

void	trim_and_fill(t_cub *cub, char *buffer, int *map_length,
	int *player_count)
{
	char	line[BUFFER_SIZE];
	int		i;
	int		j;
	int		file_lines;
	int		k;

	init_values(&i, &j, &k);
	file_lines = calc_lines(buffer);
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
		{
			line[j] = '\0';
			k++;
			if (k == file_lines)
				check_limit(line);
			else
				analyse_file(cub, line, player_count, map_length);
			j = 0;
		}
		else
			cpy_and_incr(line, buffer, &i, &j);
		i++;
	}
	cub->map.map_size += 1;
}

void	process_map(int fd, t_cub *cub, char **argv)
{
	check_file(fd, cub);
}
