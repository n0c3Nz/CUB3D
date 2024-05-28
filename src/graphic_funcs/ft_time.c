#include "CUB3D.h"
long	timenow(struct timeval *te)
{
	long	time;
	gettimeofday(te, NULL);
	time = (long)((te->tv_sec * 1000) + (te->tv_usec / 1000));
	return (time);
}
void	show_fps(t_cub *cub)
{
	char	*str;
	str = ft_itoa(cub->rnd->frametime);
	mlx_string_put(cub->mlx, cub->mlx_win, width - 50, 20, 0xFFFFFF, str);
	free(str);
}