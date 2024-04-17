/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guortun- <guortun-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 18:50:44 by guortun-          #+#    #+#             */
/*   Updated: 2024/04/06 22:47:58 by guortun-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CUB3D.h"

void	blscr_img(t_cub *cub)
{
	int		i;
	char	*p;
	int		j;

	if (!cub->img->img)
		return ;
	i = 1;
	while (i < height)
	{
		j = 1;
		while (j < width)
		{
			p = cub->img->addr + \
				(i * cub->img->line_len + j * (cub->img->bpp / 8));
			*(unsigned int *)p = 0x000000;
			j++;
		}
		i++;
	}
}

void	my_mlx_pixel_putcolor(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * (img->line_len) + x * (img->bpp / 8));
	if (!color)
		color = 0xFFFFFF;
	*(int*)pixel++ = color;
}

static void	verLine(t_cub *cub, int x, int y1, int y2)
{
	int	y;

	y = y1;
	while (y <= y2)
	{
		if ((y >= 0 && y < height) && (x >=0 && x < width))
			my_mlx_pixel_putcolor(cub->img, x, y, cub->render->verLinecolor); //mlx_pixel_put(cub->mlx, cub->img->img, x, y, cub->render->verLinecolor);
		else
			printf("(%d,%d) out of size screen\n", x, y);
		y++;
	}
}

void	calc(t_cub *cub)
{
	struct	timeval te;
	int x = 1;
	
	cub->render->oldtime = cub->render->time;
	while (x < width)
	{
		create_plans(cub, x);
		raydir(cub, x);
		raydir2(cub, x);
		ray2wall(cub);
		which_side_ray_collide(cub);

		if (cub->render->perpWallDist != 0)
			cub->render->lineHeight = (int)((double) height  / cub->render->perpWallDist);
		else
			cub->render->lineHeight = height;
		//printf("wall cast height: %d\n", cub->render->lineHeight);

		getraycoords(cub);

		// if (cub->map[cub->render->mapY][cub->render->mapX] == '1')
		// 	cub->render->verLinecolor = 0x0000FF;
		// else if (cub->map[cub->render->mapY][cub->render->mapX] == '2')
		// 	cub->render->verLinecolor = 0x00FF00;
		// else if (cub->map[cub->render->mapY][cub->render->mapX] == '3')
		// 	cub->render->verLinecolor = 0x0000FF;
		// else if (cub->map[cub->render->mapY][cub->render->mapX] == '4')
		// 	cub->render->verLinecolor = 0xFFFFFF;
		// else
		// 	cub->render->verLinecolor = 0xFFFF00;

		// if (cub->render->side == 1)
		// {
		// 	cub->render->verLinecolor = cub->render->verLinecolor / 2;

		if (cub->render->side == 1)
		{
			if (cub->render->rayDirY < 0)
			{
				//printf("OESTE\n");
				cub->render->verLinecolor = 0x355E3B; // WE 
			}
			else
			{
				//printf("EST\n");
				cub->render->verLinecolor = 0x228B22; // E 
			}
		}
		else
		{
			if (cub->render->rayDirX < 0)
			{
				//printf("NORTE\n");
				cub->render->verLinecolor = 0xf9ff70; //NORTH
			}
			else
			{
				//printf("SUR\n");
				cub->render->verLinecolor = 0x039fdb; //SUD
			}
		}
		verLine(cub, x, cub->render->drawStart, cub->render->drawEnd);
		drawfloor_ceiling(cub, x);
		cub->render->time = timenow(&te);
		cub->render->frametime = (int) (1.0 / ((cub->render->time - cub->render->oldtime) / 1000.0));
		x++;
	}
}

int	main_loop(t_cub *cub)
{
	blscr_img(cub);
	calc(cub);
	key_update(cub);
	mlx_put_image_to_window(cub->mlx, cub->mlx_win, cub->img->img, 0, 0);
	mlx_string_put(cub->mlx, cub->mlx_win, width - 50, 20, 0xFFFFFF, ft_itoa(cub->render->frametime));
	return (0);
}
