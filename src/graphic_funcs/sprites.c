#include "CUB3D.h"
static	int	ft_color(t_cub *cub)
{
	int	color;
	color = 0;
	if (cub->rnd->side == 0 && cub->rnd->rayDirX < 0)
		color = cub->sprites[2].addr[64 * cub->rnd->Ytex + cub->rnd->Xtex];
	else if (cub->rnd->side == 0 && cub->rnd->rayDirX > 0)
		color = cub->sprites[3].addr[64 * cub->rnd->Ytex + cub->rnd->Xtex];
	else if (cub->rnd->side == 1 && cub->rnd->rayDirY > 0)
		color = cub->sprites[1].addr[64 * cub->rnd->Ytex + cub->rnd->Xtex];
	else if (cub->rnd->side == 1 && cub->rnd->rayDirY < 0)
		color = cub->sprites[0].addr[64 * cub->rnd->Ytex + cub->rnd->Xtex];
	return (color);
}
static	void	ft_texture_data(t_cub *cub)
{
	double	wallx;
	if (cub->rnd->side == 0)
		wallx = cub->player.posY + cub->rnd->perpWallDist * cub->rnd->rayDirY;
	else
		wallx = cub->player.posX + cub->rnd->perpWallDist * cub->rnd->rayDirX;
	wallx -= floor(wallx);
	cub->rnd->Xtex = (int)(wallx * 64);
	if (cub->rnd->side == 0 && cub->rnd->rayDirX < 0)
		cub->rnd->Xtex = 64 - cub->rnd->Xtex - 1;
	if (cub->rnd->side == 1 && cub->rnd->rayDirY > 0)
		cub->rnd->Xtex = 64 - cub->rnd->Xtex - 1;
}
void	ft_texture_loop(t_cub *cub, int x)
{
	double	texpos;
	double	step;
	int		color;
	int		y;
	color = 0;
	ft_texture_data(cub);
	step = 1.0 * 64.0 / cub->rnd->lineHeight;
	texpos = (
			cub->rnd->drawStart - height / 2 + cub->rnd->lineHeight / 2) * step;
	y = cub->rnd->drawStart;
	while (y < cub->rnd->drawEnd + 1)
	{
		cub->rnd->Ytex = (int)texpos & (64 - 1);
		texpos += step;
		color = ft_color(cub);
		if (y * width + x < width * height)
			cub->img.addr[y * width + x] = color;
		y++;
	}
}