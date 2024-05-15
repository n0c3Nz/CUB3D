/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guortun- <guortun-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:19:29 by guortun-          #+#    #+#             */
/*   Updated: 2024/05/15 10:45:53 by guortun-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CUB3D.h"

int	check_texture_direction(t_cub **cub, char *line, int *player_count,
	int *map_length)
{
	if (*line == 'N' && *(line + 1) == 'O')
		get_texture(cub, line);
	else if (*line == 'S' && *(line + 1) == 'O')
		get_texture(cub, line);
	else if (*line == 'W' && *(line + 1) == 'E')
		get_texture(cub, line);
	else if (*line == 'E' && *(line + 1) == 'A')
		get_texture(cub, line);
	else if (*line == 'F')
	{
		if (get_color(*cub, line))
			return (1);
	}
	else if (*line == 'C')
	{
		if (get_color(*cub, line))
			return (1);
	}
	else if ((*line == '1' || *line == ' '))
	{
		if (get_map(*cub, line, player_count, map_length))
			return (1);
	}
	return (0);
}

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
	++lines;
	return (lines);
}

static void	cpy_and_incr(char *line, char *buffer, int *i, int *j)
{
	line[*j] = buffer[*i];
	(*j)++;
}

static void	init_values(int *i, int *j, int *k)
{
	*i = -1;
	*j = 0;
	*k = 0;
}

int	trim_and_fill(t_cub **cub, char *buffer, int *map_length,
	int *player_count)
{
	char	line[BUFFER];
	int		i;
	int		j;
	int		file_lines;
	int		k;

	init_values(&i, &j, &k);
	file_lines = calc_lines(buffer);
	while (buffer[++i] != '\0')
	{
		if (buffer[i] == '\n' || (buffer[i + 1] == '\0' && k < file_lines))
		{
			if (buffer[i + 1] != '\0' && k < file_lines)
				line[j] = '\0';
			k++;
			if (check_last_line(line, j, k, file_lines))
				return (1);
			else
				analyse_file(cub, line, player_count, map_length);
			j = 0;
		}
		else
			cpy_and_incr(line, buffer, &i, &j);
	}
	return (0);
}
