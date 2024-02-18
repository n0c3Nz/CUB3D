/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guortun- <guortun-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:30:22 by guortun-          #+#    #+#             */
/*   Updated: 2024/02/18 15:12:13 by guortun-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CUB3D.h"

void check_first_line(t_map *map)
{
	int i;
	char *trimed;

	i = 0;
	trimed = ft_strtrim(map->map[0], " \t");
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

static int is_player(t_map *map, char *direction, int y, int x)
{
	if (ft_strchr(direction, 'N') || ft_strchr(direction, 'S') ||
		ft_strchr(direction, 'E') || ft_strchr(direction, 'W'))
	{
		map->player_count = map->player_count + 1;
		printf("Player found at %i, %i\n", y, x - 1);
		map->player->dir = direction[0];
		map->player->x = x - 1;
		map->player->y = y;
		if (map->player_count > 1)
			return (1);
		return (0);
	}
	else
		return (1);
}

void check_body(t_map *map)
{
	int i;
	int j;
	char *trimed;

	i = 0;
	while (i < map->height)
	{
		trimed = ft_strtrim(map->map[i], " \t");
		if (ft_strlen(trimed) < 3)
		{
			printf("Error: Line %i has only %i char.\n", i, (int)ft_strlen(trimed));
			free_srcs(map);
		}
		j = 0;
		while (map->map[i][j])
		{
			//printf("Checking %c\n", map->map[i][j]);
			if (map->map[i][j] != '1' && map->map[i][j] != '0' &&
				map->map[i][j] != ' ')
			{
				if (is_player(map, &map->map[i][j], i, j) == 1)
				{
					printf("Error: Invalid character in map or +1 player\n");
					free_srcs(map);
				}
			}
			j++;
		}
		if ((map->map[i][0] != '1' && map->map[i][0] != ' ') ||
			(map->map[i][ft_strlen(map->map[i]) - 1] != '1' &&
			map->map[i][ft_strlen(map->map[i]) - 1] != ' '))
		{
			printf("\nError: Invalid first or last character in map line\n");
			free_srcs(map);
		}
		i++;
	}
	printf("Player count: %i\n", map->player_count);
}

void check_last_line(t_map *map)
{
	int i;
	char *trimed;

	i = 0;
	trimed = ft_strtrim(map->map[map->height], " \t");
	if (ft_strlen(trimed) < 3)
	{
		printf("Error: Last line has only %i char.\n", (int)ft_strlen(trimed));
		free_srcs(map);
	}
	while (i < (int)ft_strlen(trimed))
	{
		if (trimed[i] != '1')
		{
			printf("Error 1: Invalid last line: %s\n", trimed);
			free_srcs(map);
		}
		i++;
	}
}
