/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guortun- <guortun-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:59:25 by guortun-          #+#    #+#             */
/*   Updated: 2024/03/05 14:14:35 by guortun-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CUB3D.h"

void	key_update(t_map *map)
{
	if (map->key_w)//arriba y abajo tocan map->map que está dando conflicto.
	{
		if (!map->map[(int)(map->posX + map->dirX * map->moveSpeed)][(int)(map->posY)])
			map->posX += map->dirX * map->moveSpeed;
		if (!map->map[(int)(map->posX)][(int)(map->posY + map->dirY * map->moveSpeed)])
			map->posY += map->dirY * map->moveSpeed;
		printf("Has pulsado W -------- Player y[%f] x[%f]\n", map->posY, map->posX);
	}
	//move backwards if no wall behind you
	if (map->key_s)
	{
		if (!map->map[(int)(map->posX - map->dirX * map->moveSpeed)][(int)(map->posY)])
			map->posX -= map->dirX * map->moveSpeed;
		if (!map->map[(int)(map->posX)][(int)(map->posY - map->dirY * map->moveSpeed)])
			map->posY -= map->dirY * map->moveSpeed;
		printf("Has pulsado S -------- Player y[%f] x[%f]\n", map->posY, map->posX);
	}
	//rotate to the right
	if (map->key_d)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = map->dirX;
		map->dirX = map->dirX * cos(-map->rotSpeed) - map->dirY * sin(-map->rotSpeed);
		map->dirY = oldDirX * sin(-map->rotSpeed) + map->dirY * cos(-map->rotSpeed);
		double oldPlaneX = map->render.planeX;
		map->render.planeX = map->render.planeX * cos(-map->rotSpeed) - map->render.planeY * sin(-map->rotSpeed);
		map->render.planeY = oldPlaneX * sin(-map->rotSpeed) + map->render.planeY * cos(-map->rotSpeed);
		printf("Has pulsado D -------- Player y[%f] x[%f]\n", map->posY, map->posX);
	}
	//rotate to the left
	if (map->key_a)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = map->dirX;
		map->dirX = map->dirX * cos(map->rotSpeed) - map->dirY * sin(map->rotSpeed);
		map->dirY = oldDirX * sin(map->rotSpeed) + map->dirY * cos(map->rotSpeed);
		double oldPlaneX = map->render.planeX;
		map->render.planeX = map->render.planeX * cos(map->rotSpeed) - map->render.planeY * sin(map->rotSpeed);
		map->render.planeY = oldPlaneX * sin(map->rotSpeed) + map->render.planeY * cos(map->rotSpeed);
		printf("Has pulsado A -------- Player y[%f] x[%f]\n", map->posY, map->posX);
	}
	if (map->key_esc)
		exit(0);
}
int		key_press(int key, t_map *map)
{
	if (key == K_ESC)
		exit(0);
	else if (key == K_W)
		map->key_w = 1;
	else if (key == K_A)
		map->key_a = 1;
	else if (key == K_S)
		map->key_s = 1;
	else if (key == K_D)
		map->key_d = 1;
	else
		printf("Invalid key %i\n", key);
	return (0);
}

int		key_release(int key, t_map *map)
{
	if (key == K_ESC)
		exit(0);
	else if (key == K_W)
		map->key_w = 0;
	else if (key == K_A)
		map->key_a = 0;
	else if (key == K_S)
		map->key_s = 0;
	else if (key == K_D)
		map->key_d = 0;
	return (0);
}
