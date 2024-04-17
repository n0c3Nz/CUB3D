/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guortun- <guortun-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:58:48 by guortun-          #+#    #+#             */
/*   Updated: 2024/04/10 13:17:24 by guortun-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CUB3D.h"

static void	init_mlx(t_cub **cub)
{
	(*cub)->mlx = mlx_init();
	if ((*cub)->mlx == NULL)
	{
		printf("Error: mlx_init()\n      X_X\n");
		return ;
	}
	(*cub)->mlx_win = mlx_new_window((*cub)->mlx, width, height, "CUB3D");
	if ((*cub)->mlx_win == NULL)
	{
		printf("Error: mlx_init()\n      X_X\n");
		return ;
	}
	(*cub)->img->img = mlx_new_image((*cub)->mlx, width, height);
	if (!(*cub)->img->img)
	{
		printf("Error: mlx_new_image()\n    X_X\n");
		free((*cub)->mlx_win);
		return ;
	}
	(*cub)->img->addr = mlx_get_data_addr((*cub)->img->img, &(*cub)->img->bpp, \
		&(*cub)->img->line_len, &(*cub)->img->endian);
}

static void	init_keys(t_key *key)
{
	key->key_w = 0;
	key->key_a = 0;
	key->key_s = 0;
	key->key_d = 0;
	key->key_esc = 0;
}

static void	init_data(t_cub **cub, t_render **render)
{
    initialize_map_and_render(cub, render);
	init_keys(&(*cub)->key);
	init_mlx(cub);
}

int main(int argc, char **argv)
{
	t_cub		*cub;
	t_render	*render;

	render = NULL;
	init_data(&cub, &render);
	check_args(argc, argv, cub);
	int i = 0;
	while (i <= cub->map.map_size){
		printf("%s\n", cub->map.lines[i]);
		i++;
	}
	mlx_loop_hook(cub->mlx, &main_loop, cub);
	mlx_hook(cub->mlx_win, X_EVENT_KEY_PRESS, 0, &key_press, cub);
	mlx_hook(cub->mlx_win, X_EVENT_KEY_RELEASE, 0, &key_release, cub);
	//mlx_hook(cub->mlx_win, 6, 0, mouse_handler, NULL);
	//mlx_hook(cub->mlx_win, 17, 0, adios, NULL); // cruz roja window
	usleep(100);
	printf("Press W A S D to move\n");
	mlx_loop(cub->mlx);
	free_srcs(cub);
	return (0);
}
