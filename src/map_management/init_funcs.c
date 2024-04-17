/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guortun- <guortun-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 14:46:18 by guortun-          #+#    #+#             */
/*   Updated: 2024/04/08 19:15:01 by guortun-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CUB3D.h"

void	check_args(int argc, char **argv, t_cub *cub)
{
	int	fd;

	if (argc != 2)
		error_msg("Invalid number of arguments", cub);
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4))
		error_msg("Invalid file extension", cub);
	fd = open(argv[1], O_RDONLY);
	if (fd <= 0)
		error_msg("Invalid file route", cub);
	process_map(fd, cub, argv);
}

static void	get_fov(t_cub *cub)
{
	if (cub->player.dir == 'N')
		cub->player.dirY = -1.0;
	else if (cub->player.dir == 'S')
		cub->player.dirY = 1.0;
	else if (cub->player.dir == 'E')
		cub->player.dirX = 1.0;
	else if (cub->player.dir == 'W')
		cub->player.dirX = -1.0;
	cub->player.moveSpeed = 0.04;
	cub->player.rotSpeed = 0.02;
}

void	initialize_map_and_render(t_cub **cub, t_render **render)
{
	*cub = (t_cub *)malloc(1 * sizeof(t_cub));
	*render = (t_render *)malloc(1 * sizeof(t_render));
	(*cub)->img = (t_img *)malloc(1 * sizeof(t_img));
	(*cub)->render = *render;
	(*cub)->render->planeX = 0.0;
	(*cub)->render->planeY = 0.88;
	(*cub)->render->time = 0;
	(*cub)->render->oldtime = 0;
	(*cub)->map.c = 0;
	(*cub)->map.f = 0;
	(*cub)->map.no = NULL;
	(*cub)->map.so = NULL;
	(*cub)->map.we = NULL;
	(*cub)->map.ea = NULL;
	(*cub)->player.dirY = -1.0;
	(*cub)->player.dirX = 1.0;
	get_fov(*cub);
}

void	free_srcs(t_cub *cub)
{
	if (cub->render != NULL)
		free(cub->render);
	if (cub->img != NULL)
		free(cub->img);
	if (cub->mlx && cub->mlx_win)
		mlx_destroy_window(cub->mlx, cub->mlx_win);
	if (cub)
		free(cub);
	exit (0);
}
