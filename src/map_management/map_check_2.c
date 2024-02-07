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
	trimed = ft_strtrim(map->file[i], " ");
	while (trimed[0] != '1')
		trimed = ft_strtrim(map->file[i++], " ");
	map_height(map, i);
	i = map->height;
	trimed = ft_strtrim(map->file[i], " ");
	while (i < map->file_lines)
	{
		if (trimed[0] != '1' && trimed[0] != '\0')
		{
			printf("Error: Map is not found in the last instance\n");
			free_srcs(map);
		}
		trimed = ft_strtrim(map->file[i++], " ");
	}
    if (trimed[0] != '1' && trimed[0] != '\0')
    {
        printf("Error: Map is not found in the last instance\n");
        free_srcs(map);
    }
}
