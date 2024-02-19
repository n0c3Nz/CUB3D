/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guortun- <guortun-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 18:50:44 by guortun-          #+#    #+#             */
/*   Updated: 2024/02/19 14:59:37 by guortun-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CUB3D.h"

static int	key_hook(int keycode, t_map *map)
{
	if (keycode == 53)//ESC
	{
		mlx_destroy_window(map->mlx, map->mlx_win);
		free_srcs(map);
	}
	else if (keycode == 13)//W
	{
		printf("Has pulsado %i\n", keycode);//map->player->walk_dir = 1;
	}
	else if (keycode == 1)//S
	{
		printf("Has pulsado %i\n", keycode);//map->player->walk_dir = -1;
	}
	else if (keycode == 0)//A
	{
		printf("Has pulsado %i\n", keycode);//map->player->turn_dir = -1;
	}
	else if (keycode == 2)//D
	{
		printf("Has pulsado %i\n", keycode);//map->player->turn_dir = 1;
	}
	return (0);
}

void test_player_vision(t_map *map)
{
	int i;

	i = map->player->y;
	if (map->player->fov == 0)
	{
		while (i - 1 > 0)
		{
			if (map->map[i - 1][map->player->x] == '1')
				printf("Norte: Pared\n");
			else if (map->map[i - 1][map->player->x] == ' ')
				printf("Norte: Suelo\n");
			else
				printf("Norte: Vacio\n");
			i--;
		}
	}
	i = 0;
	while (i <= map->map_size)
	{
		printf("%s\n", map->map[i]);
		i++;
	}
}

void	mlx_run(t_map *map)
{
	map->mlx = mlx_init();
	mlx_do_key_autorepeaton(map->mlx);
	map->mlx_win = mlx_new_window(map->mlx, 64 * 10, 64 * 10, "CUBO");
	test_player_vision(map);
	mlx_key_hook(map->mlx_win, key_hook, map);
}
