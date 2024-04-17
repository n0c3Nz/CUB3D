/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guortun- <guortun-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:00:15 by smagniny          #+#    #+#             */
/*   Updated: 2024/04/08 12:17:37 by guortun-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CUB3D.h"

void	create_plans(t_cub *cub, int x)
{
	cub->render->cameraX = (double)(2 * x / (double)width - 1);  //coordenada x en el plano de la camara
	cub->render->rayDirX = cub->player.dirX + (cub->render->planeX * cub->render->cameraX);//direccion x del rayo en el espacio
	cub->render->rayDirY = cub->player.dirY + (cub->render->planeY * cub->render->cameraX);//direccion y del rayo en el espacio
	cub->render->mapX = (int)cub->player.posX;
	cub->render->mapY = (int)cub->player.posY;
}

void	raydir(t_cub *cub, int x)
{
	//length of ray from one x or y-side to next x or y-side
	if (cub->render->rayDirX  == 0)
		cub->render->deltaDistX = 1e30;
	else
		cub->render->deltaDistX = fabs(1 / cub->render->rayDirX);

	if (cub->render->rayDirY == 0)
		cub->render->deltaDistY = 1e30;
	else
		cub->render->deltaDistY = fabs(1 / cub->render->rayDirY);
}

void	raydir2(t_cub *cub, int x)
{
	cub->render->hit = 0; //was there a wall hit var

	if (cub->render->rayDirX < 0)//Si la direccion del rayo en x es negativa
	{
		cub->render->stepX = -1;//El rayo se mueve hacia la izquierda
		cub->render->sideDistX = (cub->player.posX - cub->render->mapX) * cub->render->deltaDistX;
		// La longitud de la distancia del rayo al siguiente lado x es igual a la posicion del jugador en x menos la posicion del jugador en x en el mapa, multiplicado por la longitud de la distancia del rayo al siguiente lado x
	}
	else
	{
		cub->render->stepX = 1;
		cub->render->sideDistX = ((cub->render->mapX + 1.0) - cub->player.posX) * cub->render->deltaDistX;
	}
	if (cub->render->rayDirY < 0)
	{
		cub->render->stepY = -1;
		cub->render->sideDistY = (cub->player.posY - cub->render->mapY) * cub->render->deltaDistY;
	}
	else
	{
		cub->render->stepY = 1;
		cub->render->sideDistY = ((cub->render->mapY + 1.0) - cub->player.posY) * cub->render->deltaDistY;
	}
}

void	ray2wall(t_cub *cub)
{
	while (cub->render->hit == 0)
	{
		//jump to next cub square, OR in x-direction, OR in y-direction
		if (cub->render->sideDistX < cub->render->sideDistY)
		{
			cub->render->sideDistX += cub->render->deltaDistX;
			cub->render->mapX += cub->render->stepX;
			cub->render->side = 0;
		}
		else
		{
			cub->render->sideDistY += cub->render->deltaDistY;
			cub->render->mapY += cub->render->stepY;
			cub->render->side = 1;
		}
		if (cub->map.lines[cub->render->mapY][cub->render->mapX] > 48)
			cub->render->hit = 1;
	}
}

// if (cub->render->side == 0)
// 	cub->render->perpWallDist = (cub->render->mapX - cub->posX + (1 - cub->render->stepX) / 2) / cub->render->rayDirX;
// else
// 	cub->render->perpWallDist = (cub->render->mapY - cub->posY + (1 - cub->render->stepY) / 2) / cub->render->rayDirY;
void	which_side_ray_collide(t_cub *cub)
{
	if (cub->render->side == 0)
		cub->render->perpWallDist = (cub->render->sideDistX
				- cub->render->deltaDistX);
	else
		cub->render->perpWallDist = (cub->render->sideDistY
				- cub->render->deltaDistY);
}

void	getraycoords(t_cub *cub)
{
	cub->render->drawStart = (-cub->render->lineHeight / 2) + (height / 2);
	if (cub->render->drawStart < 0)
		cub->render->drawStart = 0;
	cub->render->drawEnd = cub->render->lineHeight / 2 + height / 2;
	if (cub->render->drawEnd >= height)
		cub->render->drawEnd = height - 1;
}
