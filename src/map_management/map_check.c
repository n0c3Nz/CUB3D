/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guortun- <guortun-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:30:22 by guortun-          #+#    #+#             */
/*   Updated: 2024/02/09 16:38:56 by guortun-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CUB3D.h"

void	check_first_line(t_map *map)
{
	int		i;
	char	*trimed;

	i = 0;
	trimed = ft_strtrim(map->file[map->file_lines - map->height - 1], " \t");
	if (ft_strlen(trimed) < 3)
	{
		printf("Error: First line has only %i char.\n", (int)ft_strlen(trimed));
		free_srcs(map);
	}
	while (i < (int)ft_strlen(trimed))
	{
		if (trimed[i] != '1')
		{
			printf("Error 1: Invalid first line: %s\n", trimed);
			free_srcs(map);
		}
		i++;
	}
}

void check_body(t_map *map)
{
	int	i;
	int	j;

	i = map->file_lines - map->height;
	while (i < map->file_lines)
	{
		j = 0;
		while (j < (int)ft_strlen(map->file[i]))
		{
			if (map->file[i][j] != '1' && map->file[i][j] != '0' &&
				map->file[i][j] != ' ')
			{
				printf("\nError: Invalid character in map\n");
				free_srcs(map);
			}
			j++;
		}
		if ((map->file[i][0] != '1' && map->file[i][0] != ' ') ||
			(map->file[i][ft_strlen(map->file[i]) - 1] != '1' &&
			map->file[i][ft_strlen(map->file[i]) - 1] != ' '))
		{
			printf("\nError: Invalid first or last character in map line\n");
			free_srcs(map);
		}
		i++;
	}
}

