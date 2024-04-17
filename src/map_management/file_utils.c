/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guortun- <guortun-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 19:16:28 by guortun-          #+#    #+#             */
/*   Updated: 2024/04/08 19:17:56 by guortun-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CUB3D.h"

void	error_msg(char *msg, t_cub *cub)
{
	printf("Error: %s\n", msg);
	free_srcs(cub);
	exit(1);
}

void	check_limit(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != '1' && line[i] != ' ')
		{
			printf("Error: Map is not closed -> %s\n", line);
			exit(1);
		}
		i++;
	}
}

void	check_route(char *route)
{
	int	fd;

	if (*route == '\0')
	{
		printf("Error: Missing texture route\n");
		exit(1);
	}
	if (ft_strncmp(route + ft_strlen(route) - 4, ".xpm", 4))
	{
		printf("Error\nInvalid texture extension\n");
		exit(1);
	}
	fd = open(route, O_RDONLY);
	if (fd <= 0)
	{
		printf("Error: Invalid texture route\n");
		exit(1);
	}
	close(fd);
}

//Función que pasa de RGB a hexadecimal with 0x...
int	rgb_to_hex(t_cub *cub, char *rgb)
{
	char	**rgb_split;
	int		hex;
	int		i;

	i = 0;
	while (rgb[i] != '\0')
	{
		if ((rgb[i] < 48 || rgb[i] > 57) && rgb[i] != ',')
			error_msg("Invalid RGB format", cub);
		i++;
	}
	i = 0;
	rgb_split = ft_split(rgb, ',');
	if (rgb_split == NULL || rgb_split[0] == NULL
		|| rgb_split[1] == NULL || rgb_split[2] == NULL)
		error_msg("Invalid RGB format", cub);
	while (rgb_split[i] != NULL)
	{
		if (ft_atoi(rgb_split[i]) < 0 || ft_atoi(rgb_split[i]) > 255)
			error_msg("Invalid RGB format", cub);
		i++;
	}
	hex = ft_atoi(rgb_split[0]) * 65536 + ft_atoi(rgb_split[1])
		* 256 + ft_atoi(rgb_split[2]);
	return (hex);
}
