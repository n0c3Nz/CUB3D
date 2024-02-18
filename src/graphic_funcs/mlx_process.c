/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guortun- <guortun-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 18:50:44 by guortun-          #+#    #+#             */
/*   Updated: 2024/02/18 20:09:25 by guortun-         ###   ########.fr       */
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

void	mlx_run(t_map *map)
{
	map->mlx = mlx_init();
	mlx_do_key_autorepeaton(map->mlx);
	map->mlx_win = mlx_new_window(map->mlx, 64 * 10, 64 * 10, "CUBO");
	mlx_key_hook(map->mlx_win, key_hook, map);
}
