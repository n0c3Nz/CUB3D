/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 01:38:26 by guortun-          #+#    #+#             */
/*   Updated: 2024/05/14 14:32:12 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CUB3D.h"

int	get_map(t_cub *cub, char *line, int *player_count, int *map_length)
{
	int	i;

	i = 0;
	if (cub == NULL || line == NULL || player_count == NULL
		|| map_length == NULL)
		return (1);
	if (process_line(map_length, line, &i))
		return (1);
	while (line[i] != '\0')
	{
		if (line[i] == '1' || line[i] == ' ' || line[i] == '0' || line[i] == 'N'
			|| line[i] == 'S' || line[i] == 'W' || line[i] == 'E')
		{
			if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W'
				|| line[i] == 'E')
			{
				(*player_count)++;
				update_player(cub, *map_length, i, line);
			}
			i++;
		}
		else
			return (ft_putstr_err("Error: Invalid character on map\n"));
	}
	return ((*map_length)++, 0);
}

void	get_texture(t_cub **cub, char *line)
{
	if (*line == 'N' && *(line + 1) == 'O')
	{
		(*cub)->map.no = ft_strdup(line + 3);
		(*cub)->map.m_f++;
		check_route((*cub)->map.no);
	}
	else if (*line == 'S' && *(line + 1) == 'O')
	{
		(*cub)->map.so = ft_strdup(line + 3);
		(*cub)->map.m_f++;
		check_route((*cub)->map.so);
	}
	else if (*line == 'W' && *(line + 1) == 'E')
	{
		(*cub)->map.we = ft_strdup(line + 3);
		(*cub)->map.m_f++;
		check_route((*cub)->map.we);
	}
	else if (*line == 'E' && *(line + 1) == 'A')
	{
		(*cub)->map.ea = ft_strdup(line + 3);
		(*cub)->map.m_f++;
		check_route((*cub)->map.ea);
	}
}

int	get_color(t_cub *cub, char *line)
{
	char	*tmp;
	int		rgb;

	if (ft_strlen(line) < 8)
		return (ft_putstr_err("Error: Invalid RGB format\n"));
	if ((*line == 'F' || *line == 'C') && *(line + 1) == ' ')
	{
		tmp = ft_strdup(line + 2);
		rgb = rgb_to_hex(cub, tmp);
		if (rgb && *line == 'F')
			cub->map.f = rgb;
		else if (rgb && *line == 'C')
			cub->map.c = rgb;
		else
			return (ft_putstr_err("Error: Invalid RGB color\n"));
	}
	else
		return (ft_putstr_err("Error: Invalid RGB format\n"));
	return (0);
}

void	analyse_file(t_cub **cub, char *line, int *player_count
	, int *map_length)
{
	if (((*map_length > 0) && (*line != '1' && *line != ' '))
		|| (*map_length > 0) && (int)ft_strlen(line) == 0)
		error_msg("Bad character in or after map");
	else if (check_texture_direction(cub, line, player_count, map_length))
		error_msg("Bad character on map\n");
}

int	check_file(int fd, t_cub **cub)
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
		if (bytes_read == -1)
			error_msg("Error: cannot read file\n");
	}
	if (trim_and_fill(cub, buffer, &map_length, &player_count))
		return (1);
	if (player_count == 0 || player_count > 1)
		return (printf("Error: map: Invalid player count\n"), 1);
	if (map_length < 2)
		return (printf("Error: map: Map is too short\n"), 1);
	(*cub)->map.sy = map_length;
	return (check_map_data(cub, buffer));
}
