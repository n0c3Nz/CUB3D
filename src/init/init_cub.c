/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guortun- <guortun-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 21:36:17 by guortun-          #+#    #+#             */
/*   Updated: 2024/05/15 10:45:22 by guortun-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CUB3D.h"

static	void	init_keys(t_key *key);

int	initialize_map_and_rnd(t_cub **cub, t_rnd **rnd)
{
	*cub = (t_cub *)malloc(1 * sizeof(t_cub));
	if (!*cub)
		return (ft_putstr_err("Error: Unable to allocate for t_cub *\n"));
	*rnd = (t_rnd *)malloc(1 * sizeof(t_rnd));
	if (!*rnd)
	{
		free(*cub);
		return (ft_putstr_err("Error: Unable to allocate for t_rnd *\n"));
	}
	(*cub)->rnd = *rnd;
	(*cub)->rnd->time = 0;
	(*cub)->rnd->oldtime = 0;
	(*cub)->map.c = 0;
	(*cub)->map.f = 0;
	(*cub)->map.sy = 0;
	(*cub)->map.sx = 0;
	(*cub)->map.no = NULL;
	(*cub)->map.so = NULL;
	(*cub)->map.we = NULL;
	(*cub)->map.ea = NULL;
	(*cub)->player.moveSpeed = 0.04;
	(*cub)->player.rotSpeed = 0.02;
	init_keys(&(*cub)->key);
	return (0);
}

int	digest_map(int argc, char **argv, t_cub **cub)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd <= 0)
		return (ft_putstr_err("Error: Invalid file route\n"));
	if (check_file(fd, cub))
		return (1);
	close(fd);
	return (0);
}

static	void	init_keys(t_key *key)
{
	key->key_w = 0;
	key->key_a = 0;
	key->key_s = 0;
	key->key_d = 0;
	key->key_ar_l = 0;
	key->key_ar_r = 0;
	key->key_esc = 0;
}

void	set_orientation(t_player *player, double *planeX, double *planeY)
{
	int				i;
	double			length;
	const char		ors[4] = {'E', 'W', 'N', 'S'};
	const double	values[4][4] = {
	{1, 0, 0.66, 0},
	{-1, 0, -0.66, 0},
	{0, -1, 0, 0.66},
	{0, 1, 0, -0.66},
	};

	i = -1;
	while (++i < 4)
	{
		if (ors[i] == player->dir)
		{
			player->dirX = values[i][0];
			player->dirY = values[i][1];
			*planeX = values[i][2];
			*planeY = values[i][3];
			break ;
		}
	}
}
