/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guortun- <guortun-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 14:46:18 by guortun-          #+#    #+#             */
/*   Updated: 2024/02/18 14:48:44 by guortun-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CUB3D.h"

void check_args(int argc, char **argv, t_map *map)
{
	int fd;

	if (argc != 2)
	{
		printf("Error\nInvalid number of arguments\n");
		exit(1);
	}
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4))
	{
		printf("Error\nInvalid file extension\n");
		exit(1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd <= 0)
	{
		printf("Error\nInvalid file\n");
		exit(1);
	}
	process_map(fd, map, argv);
}

void initialize_map_and_player(t_map **map, t_player **player)
{
	*map = (t_map *)malloc(1 * sizeof(t_map));
	*player = (t_player *)malloc(1 * sizeof(t_player));
	(*map)->player = *player;
}

void	free_srcs(t_map *map)
{
	free(map);
	free(map->player);
	exit (0);
}