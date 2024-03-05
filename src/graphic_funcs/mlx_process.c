/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guortun- <guortun-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 18:50:44 by guortun-          #+#    #+#             */
/*   Updated: 2024/03/05 16:51:13 by guortun-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CUB3D.h"

static void	verLine(t_map *map, int x, int y1, int y2)
{
	int	y;

	y = y1;
	while (y <= y2)
	{
		mlx_pixel_put(map->mlx, map->mlx_win, x, y, map->render.verLinecolor);
		y++;
	}
}


void	calc(t_map *map)
{
	int	x;

	x = 0;
	while (x < width)
	{
		map->render.cameraX = 2 * x / (double)width - 1;//coordenada x en el plano de la camara
		map->render.rayDirX = map->dirX + map->render.planeX * map->render.cameraX;//direccion x del rayo en el espacio
		map->render.rayDirY = map->render.rayDirY + map->render.planeY * map->render.cameraX;//direccion y del rayo en el espacio
		
		map->render.mapX = (int)map->posX;//posicion x (¿del player?) en el mapa
		map->render.mapY = (int)map->posY;//posicion y (¿del player?) en el mapa

		//length of ray from current position to next x or y-side
		//double sideDistX;//Longitud de la distancia del rayo al siguiente lado x
		//double sideDistY;//Longitud de la distancia del rayo al siguiente lado y
		
		 //length of ray from one x or y-side to next x or y-side
		map->render.deltaDistX = fabs(1 / map->render.rayDirX);//Le quita el signo a la direccion del rayo en x (por si es negativo)
		map->render.deltaDistY = fabs(1 / map->render.rayDirY);//Le quita el signo a la direccion del rayo en y (por si es negativo)
		//double perpWallDist;//Distancia perpendicular a la pared
		
		//what direction to step in x or y-direction (either +1 or -1)
		//int stepX;//Direccion en la que se mueve el rayo en x
		//int stepY;//Direccion en la que se mueve el rayo en y
		
		map->render.hit = 0; //was there a wall hit?
		//int side; //was a NS or a EW wall hit?

		if (map->render.rayDirX < 0)//Si la direccion del rayo en x es negativa
		{
			map->render.stepX = -1;//El rayo se mueve hacia la izquierda
			map->render.sideDistX = (map->posX - map->render.mapX) * map->render.deltaDistX;// La longitud de la distancia del rayo al siguiente lado x es igual a la posicion del jugador en x menos la posicion del jugador en x en el mapa, multiplicado por la longitud de la distancia del rayo al siguiente lado x
		}
		else
		{
			map->render.stepX = 1;
			map->render.sideDistX = (map->render.mapX + 1.0 - map->posX) * map->render.deltaDistX;
		}
		if (map->render.rayDirY < 0)
		{
			map->render.stepY = -1;
			map->render.sideDistY = (map->posY - map->render.mapY) * map->render.deltaDistY;
		}
		else
		{
			map->render.stepY = 1;
			map->render.sideDistY = (map->render.mapY + 1.0 - map->posY) * map->render.deltaDistY;
		}

		while (map->render.hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (map->render.sideDistX < map->render.sideDistY)
			{
				map->render.sideDistX += map->render.deltaDistX;
				map->render.mapX += map->render.stepX;
				map->render.side = 0;
			}
			else
			{
				map->render.sideDistY += map->render.deltaDistY;
				map->render.mapY += map->render.stepY;
				map->render.side = 1;
			}
			//Check if ray has hit a wall
			if (map->map[map->render.mapX][map->render.mapY] > 0) map->render.hit = 1;
		}
		if (map->render.side == 0)
			map->render.perpWallDist = (map->render.mapX - map->posX + (1 - map->render.stepX) / 2) / map->render.rayDirX;
		else
			map->render.perpWallDist = (map->render.mapY - map->posY + (1 - map->render.stepY) / 2) / map->render.rayDirY;

		//Calculate height of line to draw on screen
		map->render.lineHeight = (int)(height / map->render.perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		map->render.drawStart = map->render.lineHeight / 2 + height / 2;//CUIDAO CON ESTA LINEA
		if(map->render.drawStart < 0)
			map->render.drawStart = 0;
		map->render.drawEnd = map->render.lineHeight / 2 + height / 2;
		if(map->render.drawEnd >= height)
			map->render.drawEnd = height - 1;

		//int	color;
		if (map->map[map->render.mapY][map->render.mapX] == 1)
			map->render.verLinecolor = 0xFF0000;
		else if (map->map[map->render.mapY][map->render.mapX] == 2)
			map->render.verLinecolor = 0x00FF00;
		else if (map->map[map->render.mapY][map->render.mapX] == 3)
			map->render.verLinecolor = 0x0000FF;
		else if (map->map[map->render.mapY][map->render.mapX] == 4)
			map->render.verLinecolor = 0xFFFFFF;
		else
			map->render.verLinecolor = 0xFFFF00;
		
		if (map->render.side == 1)
			map->render.verLinecolor = map->render.verLinecolor / 2;

		verLine(map, x, map->render.drawStart, map->render.drawEnd);
		
		x++;
	}
}

int	main_loop(t_map *map)
{
	//test_player_vision(map);
	calc(map);
	key_update(map);
	return (0);
}
