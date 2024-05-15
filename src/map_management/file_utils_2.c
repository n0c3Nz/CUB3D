/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guortun- <guortun-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:55:36 by guortun-          #+#    #+#             */
/*   Updated: 2024/05/15 10:46:06 by guortun-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CUB3D.h"

void	update_player(t_cub *cub, int map_length, int i, char *line)
{
	cub->player.posX = (i + 0.5);
	cub->player.posY = (map_length - 0.5);
	cub->player.dir = line[i];
}

int	validate_and_free_rgb(char **rgb_split, char *rgb)
{
	if (rgb_split == NULL || rgb_split[0] == NULL
		|| rgb_split[1] == NULL || rgb_split[2] == NULL)
	{
		free(rgb);
		free(rgb_split[2]);
		free(rgb_split[1]);
		free(rgb_split[0]);
		free(rgb_split);
		return (ft_putstr_err("Error: Invalid RGB format"));
	}
	return (0);
}

//0 is error / hex is OK
int	process_rgb(char **rgb_split, char *rgb, t_cub *cub)
{
	int	i;
	int	hex;

	if (validate_and_free_rgb(rgb_split, rgb))
		return (0);
	i = 0;
	while (rgb_split[i] != NULL)
	{
		if (ft_atoi(rgb_split[i]) < 0 || ft_atoi(rgb_split[i]) > 255)
		{
			free(rgb);
			free(rgb_split[2]);
			free(rgb_split[1]);
			free(rgb_split[0]);
			free(rgb_split);
			return (0);
		}
		i++;
	}
	hex = (ft_atoi(rgb_split[0]) * 65536) + (ft_atoi(rgb_split[1])
			* 256) + ft_atoi(rgb_split[2]);
	free(rgb);
	free(rgb_split[2]);
	free(rgb_split[1]);
	return (free(rgb_split[0]), free(rgb_split), hex);
}
