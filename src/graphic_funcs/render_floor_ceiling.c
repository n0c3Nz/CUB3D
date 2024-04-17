/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_floor_ceiling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:07:02 by smagniny          #+#    #+#             */
/*   Updated: 2024/04/02 14:09:28 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CUB3D.h"

void	drawfloor_ceiling(t_cub *cub, int x)
{
	if (cub->render->drawEnd < 0)
		cub->render->drawEnd = height;

	//draw the floor from drawEnd to the bottom of the screen and inverse. for ceiling
	for (int y = cub->render->drawEnd + 1; y < height; y++)
	{
		my_mlx_pixel_putcolor(cub->img, x, y, 0x4d0011);
		my_mlx_pixel_putcolor(cub->img, x, (height - y), 0x4d0011);
	}
}
