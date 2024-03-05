/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guortun- <guortun-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 14:46:18 by guortun-          #+#    #+#             */
/*   Updated: 2024/03/05 17:56:46 by guortun-         ###   ########.fr       */
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

void initialize_map_and_render(t_map **map, t_render **render)//, t_player **player)
{
	*map = (t_map *)malloc(1 * sizeof(t_map));
	*render = (t_render *)malloc(1 * sizeof(t_render));
	(*map)->render = *render;
	(*map)->render->planeX = 0.0;
	(*map)->render->planeY = 0.6;
}

void	ft_free_array(char **array, int size)
{
	int i;

	i = 0;
	while (i <= size)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	ft_free_array_int(int **array, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_srcs(t_map *map)
{
	if (map->map)
		ft_free_array(map->map, map->map_size);
	if (map->file)
		ft_free_array(map->file, map->file_lines - map->map_size - 2);
	if (map->c)
		ft_free_array_int(map->c, 3);
	if (map->f)
		ft_free_array_int(map->f, 3);
	/*if (map->render != NULL)
		free(map->render);*/
	if (map)
		free(map);
	if (map->mlx)
		mlx_destroy_window(map->mlx, map->mlx_win);
	exit (0);
}
