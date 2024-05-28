#include "CUB3D.h"
void	create_plans(t_cub *cub, int x)
{
	cub->rnd->cameraX = (double)(2 * x / (double)width - 1);
	cub->rnd->rayDirX = cub->player.dirX + cub->rnd->planeX * cub->rnd->cameraX;
	cub->rnd->rayDirY = cub->player.dirY + cub->rnd->planeY * cub->rnd->cameraX;
	cub->rnd->mapX = (int)cub->player.posX;
	cub->rnd->mapY = (int)cub->player.posY;
}
void	raydir(t_cub *cub, int x)
{
	if (cub->rnd->rayDirX == 0)
		cub->rnd->deltaDistX = 1e30;
	else
		cub->rnd->deltaDistX = fabs(1 / cub->rnd->rayDirX);
	if (cub->rnd->rayDirY == 0)
		cub->rnd->deltaDistY = 1e30;
	else
		cub->rnd->deltaDistY = fabs(1 / cub->rnd->rayDirY);
}
void	raydir2(t_cub *cub, int x)
{
	cub->rnd->hit = 0;
	if (cub->rnd->rayDirX < 0)
	{
		cub->rnd->stepX = -1;
		cub->rnd->sideDistX = (cub->player.posX - cub->rnd->mapX)
			* cub->rnd->deltaDistX;
	}
	else
	{
		cub->rnd->stepX = 1;
		cub->rnd->sideDistX = ((cub->rnd->mapX + 1.0) - cub->player.posX)
			* cub->rnd->deltaDistX;
	}
	if (cub->rnd->rayDirY < 0)
	{
		cub->rnd->stepY = -1;
		cub->rnd->sideDistY = (cub->player.posY - cub->rnd->mapY)
			* cub->rnd->deltaDistY;
	}
	else
	{
		cub->rnd->stepY = 1;
		cub->rnd->sideDistY = ((cub->rnd->mapY + 1.0) - cub->player.posY)
			* cub->rnd->deltaDistY;
	}
}
void	ray2wall(t_cub *cub)
{
	while (cub->rnd->hit == 0)
	{
		if (cub->rnd->sideDistX < cub->rnd->sideDistY)
		{
			cub->rnd->sideDistX += cub->rnd->deltaDistX;
			cub->rnd->mapX += cub->rnd->stepX;
			cub->rnd->side = 0;
		}
		else
		{
			cub->rnd->sideDistY += cub->rnd->deltaDistY;
			cub->rnd->mapY += cub->rnd->stepY;
			cub->rnd->side = 1;
		}
		if ((cub->rnd->mapY < cub->map.sy && cub->rnd->mapY >= 0)
			&& (cub->rnd->mapX < cub->map.sx && cub->rnd->mapX >= 0)
			&& (cub->map.lines[cub->rnd->mapY][cub->rnd->mapX] > '0'))
			cub->rnd->hit = 1;
	}
}
void	which_side_ray_collide(t_cub *cub)
{
	if (cub->rnd->side == 0)
		cub->rnd->perpWallDist = (cub->rnd->sideDistX
				- cub->rnd->deltaDistX);
	else
		cub->rnd->perpWallDist = (cub->rnd->sideDistY
				- cub->rnd->deltaDistY);
}