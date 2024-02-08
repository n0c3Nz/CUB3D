/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guortun- <guortun-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 01:38:26 by guortun-          #+#    #+#             */
/*   Updated: 2024/02/08 18:00:07 by guortun-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CUB3D.h"

void	map_height(t_map *map, int i)
{
	map->height = map->file_lines - i;
	if (map->height < 3)
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
	while (i < map->file_lines - map->height)
	{
		if (map->file[i][0] != 'N')
			i++;

	}
}

void check_map(int fd, t_map *map)
{
	char buffer[BUFFER + 1];
	ssize_t bytes_read;

	while ((bytes_read = read(fd, buffer, BUFFER)) > 0)
		buffer[bytes_read] = '\0';
	map->file = ft_split(buffer, '\n');
	map->file_lines = count_lines(map->file);
	check_map_pos(map);
	element_finder(map);
	printf("C RGB: %i %i %i\nF RGB: %i %i %i", map->c[0][0], map->c[1][0], map->c[2][0], map->f[0][0], map->f[1][0], map->f[2][0]);
	check_first_line(map);
	printf("\nNumber of lines: %i\nMap height: %i\n", map->file_lines, map->height);
	printf("First line of map: (%i) -> (%s)\n", map->file_lines - map->height, map->file[map->file_lines - map->height - 1]);
	//check_body(map);
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

void	rgb_is_digit(char **strs)
{
	int	i;
	int	j;

	i = 0;
	while (strs[i])
	{
		j = 0;
		while (strs[i][j])
		{
			if (!ft_isdigit(strs[i][j]))
			{
				printf("Error: RGB is not a digit\n");
				exit(1);
			}
			j++;
		}
		i++;
	}
}