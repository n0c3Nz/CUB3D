/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeee.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guortun- <guortun-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 12:47:18 by smagniny          #+#    #+#             */
/*   Updated: 2024/05/15 10:46:31 by guortun-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/CUB3D.h"

void	free_map(t_cub *cub)
{
	int	i;

	i = 0;
	if (cub->map.m_f-- > 0)
		free(cub->map.no);
	if (cub->map.m_f-- > 0)
		free(cub->map.so);
	if (cub->map.m_f-- > 0)
		free(cub->map.we);
	if (cub->map.m_f-- > 0)
		free(cub->map.ea);
	exit(0);
}

int	ft_exit_free_img_error(t_cub *cub)
{
	mlx_destroy_image(cub->mlx, cub->img.img);
	if (cub->map.m_f-- > 0)
		mlx_destroy_image(cub->mlx, cub->sprites[0].img);
	if (cub->map.m_f-- > 0)
		mlx_destroy_image(cub->mlx, cub->sprites[1].img);
	if (cub->map.m_f-- > 0)
		mlx_destroy_image(cub->mlx, cub->sprites[2].img);
	if (cub->map.m_f-- > 0)
		mlx_destroy_image(cub->mlx, cub->sprites[3].img);
	if (cub->map.m_f-- > 0)
		mlx_destroy_window(cub->mlx, cub->mlx_win);
	free_map(cub);
	return (1);
}

int	ft_exit_free_img(t_cub *cub)
{
	mlx_destroy_image(cub->mlx, cub->img.img);
	mlx_destroy_image(cub->mlx, cub->sprites[0].img);
	mlx_destroy_image(cub->mlx, cub->sprites[1].img);
	mlx_destroy_image(cub->mlx, cub->sprites[2].img);
	mlx_destroy_image(cub->mlx, cub->sprites[3].img);
	mlx_destroy_window(cub->mlx, cub->mlx_win);
	free_map(cub);
	return (0);
}

void	error_msg(char *msg)
{
	ft_putstr_err(msg);
	exit(1);
}

int	ft_putstr_err(char *str)
{
	ft_putstr_fd(str, 2);
	return (1);
}
