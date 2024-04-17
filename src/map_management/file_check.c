/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guortun- <guortun-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 01:38:26 by guortun-          #+#    #+#             */
/*   Updated: 2024/04/08 20:06:59 by guortun-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CUB3D.h"

static void	get_map(t_cub *cub, char *line, int *player_count, int *map_length)
{
	int	i;

	i = 0;
	if (*map_length == 0)
	{
		check_limit(line);
		(*map_length)++;
		return ;
	}
	while (line[i] == '0')
		i++;
	if (ft_strlen(line) < 3)
		error_msg("Line of map is too short", cub);
	if ((line[i] != '1' && line[i] != ' ') || (line[ft_strlen(line) - 1] != '1'
			&& line[ft_strlen(line) - 1] != ' '))
		error_msg("Map is not closed", cub);
	while (line[i] != '\0')
	{
		if (line[i] == '1' || line[i] == ' ' || line[i] == '0' || line[i] == 'N'
			|| line[i] == 'S' || line[i] == 'W' || line[i] == 'E')
		{
			if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W'
				|| line[i] == 'E')
			{
				(*player_count)++;
				cub->player.posX = i;
				cub->player.posY = *map_length;
				cub->player.dir = line[i];
			}
			i++;
		}
		else
			error_msg("Invalid character on map", cub);
	}
	(*map_length)++;
}

static void	get_texture(t_cub *cub, char *line)
{
	if (*line == 'N' && *(line + 1) == 'O')
	{
		cub->map.no = ft_strdup(line + 3);
		check_route(cub->map.no);
	}
	else if (*line == 'S' && *(line + 1) == 'O')
	{
		cub->map.so = ft_strdup(line + 3);
		check_route(cub->map.so);
	}
	else if (*line == 'W' && *(line + 1) == 'E')
	{
		cub->map.we = ft_strdup(line + 3);
		check_route(cub->map.we);
	}
	else if (*line == 'E' && *(line + 1) == 'A')
	{
		cub->map.ea = ft_strdup(line + 3);
		check_route(cub->map.ea);
	}
}

static void	get_color(t_cub *cub, char *line)
{
	char	*tmp;

	if (*line == 'F' && *(line + 1) == ' ')
	{
		tmp = ft_strdup(line + 2);
		cub->map.f = rgb_to_hex(cub, tmp);
	}
	else if (*line == 'C' && *(line + 1) == ' ')
	{
		tmp = ft_strdup(line + 2);
		cub->map.c = rgb_to_hex(cub, tmp);
	}
	else
		error_msg("Invalid Ceiling or Floor color", cub);
}

void	analyse_file(t_cub *cub, char *line, int *player_count, int *map_length)
{
	if ((*map_length > 0) && (*line != '1' && *line != ' '))
		error_msg("Bad character in or after map", cub);
	if (*line == 'N' && *(line + 1) == 'O')
		get_texture(cub, line);
	else if (*line == 'S' && *(line + 1) == 'O')
		get_texture(cub, line);
	else if (*line == 'W' && *(line + 1) == 'E')
		get_texture(cub, line);
	else if (*line == 'E' && *(line + 1) == 'A')
		get_texture(cub, line);
	else if (*line == 'F')
		get_color(cub, line);
	else if (*line == 'C')
		get_color(cub, line);
	else if (*line == '1' || *line == ' ')
		get_map(cub, line, player_count, map_length);
	else if (*line == '\0')
		return ;
	else
		error_msg("Invalid character on file", cub);
}

void	check_file(int fd, t_cub *cub)
{
	ssize_t	bytes_read;
	char	buffer[BUFFER];
	int		map_length;
	int		player_count;

	map_length = 0;
	player_count = 0;
	bytes_read = read(fd, buffer, BUFFER);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		bytes_read = read(fd, buffer, BUFFER);
	}
	trim_and_fill(cub, buffer, &map_length, &player_count);
	if (player_count == 0 || player_count > 1)
		error_msg("Invalid player count", cub);
	if (map_length < 2)
		error_msg("Map is too short", cub);
	cub->map.map_size = map_length;
	if (cub->map.no == NULL || cub->map.so == NULL
		|| cub->map.we == NULL || cub->map.ea == NULL)
		error_msg("Missing texture", cub);
	if (cub->map.f == 0 || cub->map.c == 0)
		error_msg("Missing color", cub);
	fill_map(cub, buffer);
}
