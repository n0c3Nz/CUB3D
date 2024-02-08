/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guortun- <guortun-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:19:29 by guortun-          #+#    #+#             */
/*   Updated: 2024/02/08 16:16:04 by guortun-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CUB3D.h"

void process_map(int fd, t_map *map, char **argv)
{
	int i;

	i = go_to_map(fd);
	close(fd);
	fd = open(argv[1], O_RDONLY);
	if (fd <= 0)
	{
		printf("Error\nInvalid file\n");
		exit(1);
	}
	if (i)
		check_map(fd, map);
	else {
		printf("Error: No map detected\n");
		exit(1);
	}
	close(fd);
}

int go_to_map(int fd)
{
	char *line;

	line = get_next_line(fd);
	if (line == NULL)
	{
		printf("Error: Empty file\n");
		exit(-1);
	}
	if (line[0] == '1')
	{
		free(line);
		return (1);
	}
	while (line)
	{
		if (line[0] == '1')
		{
			free(line);
			return (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (0);
}

void check_map_pos(t_map *map)
{
	int		i;
	char	*trimed;

	i = 0;
	trimed = ft_strtrim(map->file[i], " \t");
	while (trimed[0] != '1')
		trimed = ft_strtrim(map->file[i++], " \t");
	map_height(map, i);
	i = map->height;
	while (i < map->file_lines)
	{
		if (trimed[0] != '1' && trimed[0] != '\0')
		{
			printf("Error: Map is not found in the last instance -> %s\n", trimed);
			free_srcs(map);
		}
		trimed = ft_strtrim(map->file[i++], " \t");
	}
    if (trimed[0] != '1' && trimed[0] != '\0')
    {
        printf("Error: Map is not found in the last instance\n");
        free_srcs(map);
    }
}

static void is_valid_rute(char *str, t_map *map, char *rute)
{
	char *trimed;
	int	fd;

	str+= 2;
	trimed = ft_strtrim(str, " \t");
	if (trimed)
	{
		fd = open(trimed, O_RDONLY);
		if (fd <= 0)
		{
			printf("Error: Invalid rute\n");
			close(fd);
			free_srcs(map);
		}
		else
		{
			close(fd);
			rute_filler(map, rute, trimed);
		}
	}
	else
	{
		printf("Error: No rute specified\n");
		free_srcs(map);
	}
}

void	element_finder(t_map *map)
{
	int	i;

	i = 0;
	while ( i < map->file_lines - map->height - 1)
	{
		if ((ft_strnstr(map->file[i], "NO", 2) != 0))
			is_valid_rute(map->file[i], map, "NO");
		else if ((ft_strnstr(map->file[i], "SO", 2) != 0))
			is_valid_rute(map->file[i], map, "SO");
		else if ((ft_strnstr(map->file[i], "WE", 2) != 0))
			is_valid_rute(map->file[i], map, "WE");
		else if ((ft_strnstr(map->file[i], "EA", 2) != 0))
			is_valid_rute(map->file[i], map, "EA");
		else if ((ft_strnstr(map->file[i], "C", 1) != 0))
			is_valid_rgb(map->file[i], map, 'C');
		else if ((ft_strnstr(map->file[i], "F", 1) != 0))
			is_valid_rgb(map->file[i], map, 'F');
		i++;
	}
	if (map->no == NULL || map->so == NULL || map->we == NULL ||
		map->ea == NULL)
	{
		printf("Error: Missing rute\n");
		free_srcs(map);
	}
}
