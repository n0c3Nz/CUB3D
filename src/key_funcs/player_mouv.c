#include "CUB3D.h"
void	mouv_player_left(t_cub *cub)
{
	int	x;
	int	y;
	int	xx;
	int	yy;
	x = (int)cub->player.posX;
	y = (int)cub->player.posY;
	xx = (int)(cub->player.posX - cub->player.dirY * cub->player.moveSpeed);
	yy = (int)(cub->player.posY + cub->player.dirX * cub->player.moveSpeed);
	if (cub->map.lines[y][xx] == '0')
		cub->player.posX -= cub->player.dirY * cub->player.moveSpeed;
	if (cub->map.lines[yy][x] == '0')
		cub->player.posY += cub->player.dirX * cub->player.moveSpeed;
}
void	mouv_player_right(t_cub *cub)
{
	int	x;
	int	y;
	int	xx;
	int	yy;
	x = (int)cub->player.posX;
	y = (int)cub->player.posY;
	xx = (int)(cub->player.posX + cub->player.dirY * cub->player.moveSpeed);
	yy = (int)(cub->player.posY - cub->player.dirX * cub->player.moveSpeed);
	if (cub->map.lines[y][xx] == '0')
		cub->player.posX += cub->player.dirY * cub->player.moveSpeed;
	if (cub->map.lines[yy][x] == '0')
		cub->player.posY -= cub->player.dirX * cub->player.moveSpeed;
}
void	rotate_player_right(t_cub *cub)
{
	double	old_dirx;
	double	old_planex;
	old_dirx = cub->player.dirX;
	cub->player.dirX = cub->player.dirX * cos(cub->player.rotSpeed)
		- cub->player.dirY * sin(cub->player.rotSpeed);
	cub->player.dirY = old_dirx * sin(cub->player.rotSpeed)
		+ cub->player.dirY * cos(cub->player.rotSpeed);
	old_planex = cub->rnd->planeX;
	cub->rnd->planeX = cub->rnd->planeX * cos(cub->player.rotSpeed)
		- cub->rnd->planeY * sin(cub->player.rotSpeed);
	cub->rnd->planeY = old_planex * sin(cub->player.rotSpeed)
		+ cub->rnd->planeY * cos(cub->player.rotSpeed);
}
void	rotate_player_left(t_cub *cub)
{
	double	old_dirx;
	double	old_planex;
	old_dirx = cub->player.dirX;
	cub->player.dirX = cub->player.dirX * cos(-cub->player.rotSpeed)
		- cub->player.dirY * sin(-cub->player.rotSpeed);
	cub->player.dirY = old_dirx * sin(-cub->player.rotSpeed)
		+ cub->player.dirY * cos(-cub->player.rotSpeed);
	old_planex = cub->rnd->planeX;
	cub->rnd->planeX = cub->rnd->planeX * cos(-cub->player.rotSpeed)
		- cub->rnd->planeY * sin(-cub->player.rotSpeed);
	cub->rnd->planeY = old_planex * sin(-cub->player.rotSpeed)
		+ cub->rnd->planeY * cos(-cub->player.rotSpeed);
}
void	mouv_backwards(t_cub *cub)
{
	if (cub->map.lines[(int)(cub->player.posY)]
		[(int)(cub->player.posX - cub->player.dirX
			* cub->player.moveSpeed)] == '0')
		cub->player.posX -= cub->player.dirX * cub->player.moveSpeed;
	if (cub->map.lines[(int)(cub->player.posY
			- cub->player.dirY * cub->player.moveSpeed)]
		[(int)(cub->player.posX)] == '0')
		cub->player.posY -= cub->player.dirY * cub->player.moveSpeed;
}