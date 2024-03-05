/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guortun- <guortun-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:58:48 by guortun-          #+#    #+#             */
/*   Updated: 2024/03/05 17:54:48 by guortun-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CUB3D.h"

static void init_data(t_map **map, t_render **render)
{
    initialize_map_and_render(map, render);
    
	(*map)->mlx = mlx_init();
	(*map)->mlx_win = mlx_new_window((*map)->mlx, width, height, "CUB3D");
	(*map)->texWidth = 64;
	(*map)->texHeight = 64;
}

int main(int argc, char **argv)
{
	t_map		*map;
	t_render	*render;
	render = NULL;

	init_data(&map, &render);
	check_args(argc, argv, map);
	mlx_loop_hook(map->mlx, &main_loop, map);
	mlx_hook(map->mlx_win, X_EVENT_KEY_PRESS, 0, &key_press, map);
	mlx_hook(map->mlx_win, X_EVENT_KEY_RELEASE, 0, &key_release, map);
	mlx_loop(map->mlx);
	free_srcs(map);
	return (0);
}
