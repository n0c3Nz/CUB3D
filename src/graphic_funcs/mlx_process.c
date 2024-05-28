#include "CUB3D.h"
void	blscr_img(t_cub *cub)
{
	int		i;
	char	*p;
	int		j;
	if (!cub->img.img)
		return ;
	i = 1;
	while (i < height)
	{
		j = 1;
		while (j < width)
		{
			if (i * width + j < width * height)
				cub->img.addr[i * width + j] = 0x000000;
			j++;
		}
		i++;
	}
}
void	calc(t_cub *cub)
{
	struct timeval	te;
	int				x;
	x = 1;
	cub->rnd->oldtime = cub->rnd->time;
	while (x < width)
	{
		create_plans(cub, x);
		raydir(cub, x);
		raydir2(cub, x);
		ray2wall(cub);
		which_side_ray_collide(cub);
		if (cub->rnd->perpWallDist != 0)
			cub->rnd->lineHeight = (int)((double) height
					/ cub->rnd->perpWallDist);
		else
			cub->rnd->lineHeight = height;
		getraycoords(cub);
		drawfloor_ceiling(cub, x);
		ft_texture_loop(cub, x);
		cub->rnd->time = timenow(&te);
		cub->rnd->frametime = (int)(
				1.0 / ((cub->rnd->time - cub->rnd->oldtime) / 1000.0));
		x++;
	}
}
int	main_loop(t_cub *cub)
{
	blscr_img(cub);
	calc(cub);
	key_update(cub);
	mlx_put_image_to_window(cub->mlx, cub->mlx_win, cub->img.img, 0, 0);
	show_fps(cub);
	return (0);
}