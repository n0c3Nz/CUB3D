#include "CUB3D.h"

void dump_map(t_map *map)
{
	int i;
	int j;
	int map_lines;

	j = 0;
	map_lines = map->file_lines - map->height;
	map->map = malloc(sizeof(char *) * map_lines + 1);
	i = map->height - 1;
	while (i < map->file_lines)
		map->map[j++] = map->file[i++];
	map->map[j] = NULL;
}

void	rute_filler(t_map *map, char *rute, char *valid_rute)
{
	if ((ft_strnstr(rute, "NO", 2) != 0))
		map->no = valid_rute;
	else if ((ft_strnstr(rute, "SO", 2) != 0))
		map->so = valid_rute;
	else if ((ft_strnstr(rute, "WE", 2) != 0))
		map->we = valid_rute;
	else if ((ft_strnstr(rute, "EA", 2) != 0))
		map->ea = valid_rute;
}

void	is_valid_rgb(char *str, t_map *map, char id)
{
	char *trimed;

	str++;
	trimed = ft_strtrim(str, " \t,");
	if (ft_strlen(trimed) > 0)
	{
		if (id == 'C')
			map->c = ft_split_int(trimed, ',');
		else if (id == 'F')
			map->f = ft_split_int(trimed, ',');
	}
	else
	{
		printf("Error: No RGB specified\n");
		free_srcs(map);
	}
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