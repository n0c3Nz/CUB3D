/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guortun- <guortun-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:59:25 by guortun-          #+#    #+#             */
/*   Updated: 2024/05/15 10:45:40 by guortun-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CUB3D.h"

static	void	mouv_forward(t_cub *cub)
{
	if (cub->map.lines[(int)(cub->player.posY)]
		[(int)
			(cub->player.posX
				+ cub->player.dirX * cub->player.moveSpeed)] == '0')
		cub->player.posX += cub->player.dirX * cub->player.moveSpeed;
	if (cub->map.lines[(int)
			(cub->player.posY + cub->player.dirY * cub->player.moveSpeed)]
		[(int)(cub->player.posX)] == '0')
		cub->player.posY += cub->player.dirY * cub->player.moveSpeed;
}

void	key_update(t_cub *cub)
{
	if (cub->key.key_w)
		mouv_forward(cub);
	else if (cub->key.key_s)
		mouv_backwards(cub);
	else if (cub->key.key_d)
		mouv_player_left(cub);
	else if (cub->key.key_a)
		mouv_player_right(cub);
	else if (cub->key.key_ar_l)
		rotate_player_left(cub);
	else if (cub->key.key_ar_r)
		rotate_player_right(cub);
}

int	key_press(int key, t_cub *cub)
{
	if (key == K_ESC)
		exit(0);
	else if (key == K_W)
		cub->key.key_w = 1;
	else if (key == K_S)
		cub->key.key_s = 1;
	else if (key == K_A)
		cub->key.key_a = 1;
	else if (key == K_D)
		cub->key.key_d = 1;
	else if (key == K_AR_R)
		cub->key.key_ar_r = 1;
	else if (key == K_AR_L)
		cub->key.key_ar_l = 1;
	return (0);
}

int	key_release(int key, t_cub *cub)
{
	if (key == K_ESC)
		exit(0);
	else if (key == K_W)
		cub->key.key_w = 0;
	else if (key == K_S)
		cub->key.key_s = 0;
	else if (key == K_A)
		cub->key.key_a = 0;
	else if (key == K_D)
		cub->key.key_d = 0;
	else if (key == K_AR_R)
		cub->key.key_ar_r = 0;
	else if (key == K_AR_L)
		cub->key.key_ar_l = 0;
	return (0);
}
