/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guortun- <guortun-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 01:38:26 by guortun-          #+#    #+#             */
/*   Updated: 2024/03/05 17:57:47 by guortun-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CUB3D.h"

void	map_height(t_map *map, int i)
{
	map->map_height = i;
	map->map_size = map->file_lines - i;
	if (map->map_height < 3)
	{
		printf("Error 5: Invalid size map\n");
		exit(1);
	}
}

int count_lines(char **file)
{
	int count;

	count = 0;
	while (file[count] != NULL)
		count++;
	return count;
}

void check_items(t_map *map)
{
	int	i;

	i = 0;	
	while (i < map->file_lines - map->map_height)
	{
		if (map->file[i][0] != 'N')
			i++;

	}
}

void check_map(int fd, t_map *map)
{
	char buffer[BUFFER + 1];
	ssize_t bytes_read;

	printf("DEBUGGING SEGFAULT\n");
	while ((bytes_read = read(fd, buffer, BUFFER)) > 0)
		buffer[bytes_read] = '\0';
	map->player_count = 0;
	map->file = ft_split(buffer, '\n');
	map->file_lines = count_lines(map->file);
	check_map_pos(map);
	element_finder(map);
	printf("\nC RGB: %i %i %i\nF RGB: %i %i %i\n", map->c[0][0], map->c[1][0], map->c[2][0], map->f[0][0], map->f[1][0], map->f[2][0]);
	dump_map(map);
	check_first_line(map);
	check_body(map);
	check_last_line(map);
	printf("\nNumber of lines: %i\nMap height: %i\n", map->file_lines, map->map_height);
}

int		**ft_split_int(char *s, char c)
{
    char	**strs;
    int		**ints;
    int		i;
    int		count;

    strs = ft_split(s, c);
    i = 0;
	rgb_is_digit(strs);
    count = 0;
    while (strs[i])
    {
        count++;
        i++;
    }
    ints = (int **)malloc(sizeof(int *) * count);
    i = 0;
    while (i < count)
    {
        ints[i] = (int *)malloc(sizeof(int));
        *ints[i] = ft_atoi(strs[i]);
        i++;
    }
    return (ints);
}
