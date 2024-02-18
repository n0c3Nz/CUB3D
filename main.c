/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guortun- <guortun-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:58:48 by guortun-          #+#    #+#             */
/*   Updated: 2024/02/18 18:51:04 by guortun-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CUB3D.h"

static void init_data(t_map **map, t_player **player, int argc, char **argv)
{
    initialize_map_and_player(map, player);
    check_args(argc, argv, *map);
}

int main(int argc, char **argv)
{
	t_map *map;
	t_player *player;

	init_data(&map, &player, argc, argv);
	mlx_run(map);
	mlx_loop(map->mlx);
	free_srcs(map);
	return (0);
}
