#include "CUB3D.h"
void	drawfloor_ceiling(t_cub *cub, int x)
{
	int	y;
	y = cub->rnd->drawEnd + 1;
	if (cub->rnd->drawEnd < 0)
		cub->rnd->drawEnd = height;
	while (y < height)
	{
		if (y * width + x < width * height && (y > 0 && x > 0))
		{
			cub->img.addr[y * width + x] = cub->map.c;
			cub->img.addr[(height - y) * width + x] = cub->map.f;
		}
		y++;
	}
}