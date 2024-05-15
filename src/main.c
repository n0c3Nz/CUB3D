/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guortun- <guortun-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:44:35 by guortun-          #+#    #+#             */
/*   Updated: 2024/05/14 11:13:12 by guortun-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CUB3D.h"

static	int	init_cub(int argc, char **argv, t_cub **cub, t_rnd **rnd)
{
	if (first_check(argc, argv))
		exit (1);
	if (initialize_map_and_rnd(cub, rnd))
		exit (1);
	if (digest_map(argc, argv, cub))
		exit (1);
	set_orientation(&(*cub)->player, &(*cub)->rnd->planeY,
		&(*cub)->rnd->planeX);
	if (init_mlx(cub))
		exit (ft_exit_free_img_error((*cub)));
	return (0);
}

int	main(int argc, char **argv)
{
	t_cub		*cub;
	t_rnd		*rnd;

	rnd = NULL;
	if (init_cub(argc, argv, &cub, &rnd))
		return (1);
	mlx_loop_hook(cub->mlx, &main_loop, cub);
	mlx_hook(cub->mlx_win, 2, 1L << 0, &key_press, cub);
	mlx_hook(cub->mlx_win, 3, 1L << 1, &key_release, cub);
	mlx_hook(cub->mlx_win, 17, 0L, ft_exit_free_img, cub);
	mlx_loop(cub->mlx);
	return (0);
}
