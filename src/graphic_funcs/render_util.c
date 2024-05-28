#include "CUB3D.h"
void	getraycoords(t_cub *cub)
{
	cub->rnd->drawStart = (-cub->rnd->lineHeight / 2) + (height / 2);
	if (cub->rnd->drawStart < 0)
		cub->rnd->drawStart = 0;
	cub->rnd->drawEnd = cub->rnd->lineHeight / 2 + height / 2;
	if (cub->rnd->drawEnd >= height)
		cub->rnd->drawEnd = height - 1;
}