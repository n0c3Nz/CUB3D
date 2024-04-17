/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guortun- <guortun-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:59:25 by guortun-          #+#    #+#             */
/*   Updated: 2024/04/08 12:30:17 by guortun-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CUB3D.h"

void	key_update(t_cub *cub)
{
	if (cub->key.key_w)
	{
		if (cub->map.lines[(int)(cub->player.posY)][(int)(cub->player.posX + cub->player.dirX * cub->player.moveSpeed)] == '0')
			cub->player.posX += cub->player.dirX * cub->player.moveSpeed;

		if (cub->map.lines[(int)(cub->player.posY + cub->player.dirY * cub->player.moveSpeed)][(int)(cub->player.posX)] == '0')
			cub->player.posY += cub->player.dirY * cub->player.moveSpeed;
		//printf("Has pulsado W -------- Player y[%f] x[%f]\n", cub->player.posY, cub->player.posX);
	}
	if (cub->key.key_s)
	{
		if (cub->map.lines[(int)(cub->player.posY)][(int)(cub->player.posX - cub->player.dirX * cub->player.moveSpeed)] == '0')
			cub->player.posX -= cub->player.dirX * cub->player.moveSpeed;
		if (cub->map.lines[(int)(cub->player.posY - cub->player.dirY * cub->player.moveSpeed)][(int)(cub->player.posX)] == '0')
			cub->player.posY -= cub->player.dirY * cub->player.moveSpeed;
		//printf("Has pulsado S -------- Player y[%f] x[%f]\n", cub->player.posY, cub->player.posX);
	}
	if (cub->key.key_a)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = cub->player.dirX;
		cub->player.dirX = cub->player.dirX * cos(-cub->player.rotSpeed) - cub->player.dirY * sin(-cub->player.rotSpeed);
		cub->player.dirY = oldDirX * sin(-cub->player.rotSpeed) + cub->player.dirY * cos(-cub->player.rotSpeed);
		double oldPlaneX = cub->render->planeX;
		cub->render->planeX = cub->render->planeX * cos(-cub->player.rotSpeed) - cub->render->planeY * sin(-cub->player.rotSpeed);
		cub->render->planeY = oldPlaneX * sin(-cub->player.rotSpeed) + cub->render->planeY * cos(-cub->player.rotSpeed);
		//printf("Has pulsado D -------- Player y[%f] x[%f]\n", cub->player.posY, cub->player.posX);
	}
	//rotate to the left
	if (cub->key.key_d)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = cub->player.dirX;
		cub->player.dirX = cub->player.dirX * cos(cub->player.rotSpeed) - cub->player.dirY * sin(cub->player.rotSpeed);
		cub->player.dirY = oldDirX * sin(cub->player.rotSpeed) + cub->player.dirY * cos(cub->player.rotSpeed);
		double oldPlaneX = cub->render->planeX;
		cub->render->planeX = cub->render->planeX * cos(cub->player.rotSpeed) - cub->render->planeY * sin(cub->player.rotSpeed);
		cub->render->planeY = oldPlaneX * sin(cub->player.rotSpeed) + cub->render->planeY * cos(cub->player.rotSpeed);
		//printf("Has pulsado A -------- Player y[%f] x[%f]\n", cub->player.posY, cub->player.posX);
	}
	if (cub->key.key_esc)
	{
		printf("Hola\n");
		exit(0);
	}
}

int		key_press(int key, t_cub *cub)
{
	if (key == K_ESC)
		exit(0);
	else if (key == K_W)
		cub->key.key_w = 1;
	else if (key == K_A || key == K_AR_L)
		cub->key.key_a = 1;
	else if (key == K_S)
		cub->key.key_s = 1;
	else if (key == K_D || key == K_AR_R)
		cub->key.key_d = 1;
	else
		printf("Invalid key %i\n", key);
	return (0);
}

int		key_release(int key, t_cub *cub)
{
	if (key == K_ESC)
		exit(0);
	else if (key == K_W)
		cub->key.key_w = 0;
	else if (key == K_A || key == K_AR_L)
		cub->key.key_a = 0;
	else if (key == K_S)
		cub->key.key_s = 0;
	else if (key == K_D || key == K_AR_R)
		cub->key.key_d = 0;
	else
		printf("Invalid key %i\n", key);
	return (0);
}


int	adios(t_cub *cub)
{
	mlx_destroy_window(cub->mlx, cub->mlx_win);
	free_srcs(cub);
	return (0);
}
