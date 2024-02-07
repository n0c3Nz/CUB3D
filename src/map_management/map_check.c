/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guortun- <guortun-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 01:38:26 by guortun-          #+#    #+#             */
/*   Updated: 2024/02/07 03:51:08 by guortun-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CUB3D.h"

void	map_height(t_map *map, int i)
{
	map->height = map->file_lines - i;
	if (map->height < 3)
	{
		printf("Error 5: Invalid size map\n");
		exit(1);
	}
}

void	check_first_line(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map->file[i][0] != '1')
		i++;
	while (j < (int)ft_strlen(map->file[i]))
	{
		if (map->file[i][j] != '1')
		{
			printf("Error 1: Invalid first line: %s\n", map->file[i]);
			exit(0);
		}
		j++;
	}
}

void check_body(char *line)
{
	int i = 0;

	if (line[i] != '1')
	{
		printf("%c\n", line[i]);
		printf("Error 2: Invalid map\n");
		exit(1);
	}
	while (line[i] != '\0' && line[i] != '\n')
	{
		if (line[i] != '1' && line[i] != '0')
		{
			printf("%c\n", line[i]);
			printf("Error 3: Invalid map\n");
			exit(1);
		}
		i++;
	}
	if (line[i - 1] != '1')
	{
		printf("%c\n", line[i - 1]);
		printf("Error 4: Invalid map\n");
		exit(1);
	}
}

int count_lines(char **file)
{
	int count;

	count = 0;
	while (file[count] != NULL)
		count++;
	return count;
}

void check_map(int fd, t_map *map)
{
	char buffer[BUFFER + 1];
	ssize_t bytes_read;

	while ((bytes_read = read(fd, buffer, BUFFER)) > 0)
		buffer[bytes_read] = '\0';
	map->file = ft_split(buffer, '\n');
	map->file_lines = count_lines(map->file);
	check_map_pos(map);
	check_first_line(map);
	//check_body(map);
}
