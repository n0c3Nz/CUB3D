#include "CUB3D.h"

void	check_first_line(t_map *map)
{
	int		i;
	char	*trimed;

	i = 0;
	trimed = ft_strtrim(map->file[map->file_lines - map->height - 1], " \t");
	if (ft_strlen(trimed) < 3)
	{
		printf("Error: First line has only %i char.\n", (int)ft_strlen(trimed));
		free_srcs(map);
	}
	while (i < (int)ft_strlen(trimed))
	{
		if (trimed[i] != '1')
		{
			printf("Error 1: Invalid first line: %s\n", trimed);
			free_srcs(map);
		}
		i++;
	}
}

void check_body(char *line)
{
	int i = 0;

	if (line[i] != '1')
	{
		printf("%c\n", line[i]);
		printf("Error 2: Invalid map\n");
		exit(1);
	}
	while (line[i] != '\0' && line[i] != '\n')
	{
		if (line[i] != '1' && line[i] != '0')
		{
			printf("%c\n", line[i]);
			printf("Error 3: Invalid map\n");
			exit(1);
		}
		i++;
	}
	if (line[i - 1] != '1')
	{
		printf("%c\n", line[i - 1]);
		printf("Error 4: Invalid map\n");
		exit(1);
	}
}

