#include "CUB3D.h"

static void check_args(int argc, char **argv, t_map *map)
{
	int fd;

	if (argc != 2)
	{
		printf("Error\nInvalid number of arguments\n");
		exit(1);
	}
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4))
	{
		printf("Error\nInvalid file extension\n");
		exit(1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd <= 0)
	{
		printf("Error\nInvalid file\n");
		exit(1);
	}
	process_map(fd, map, argv);
}

static void initialize_map_and_player(t_map **map, t_player **player)
{
	*map = (t_map *)malloc(1 * sizeof(t_map));
	*player = (t_player *)malloc(1 * sizeof(t_player));
	(*map)->player = *player;
}

void	free_srcs(t_map *map)
{
	free(map);
	free(map->player);
	exit (0);
}

int main(int argc, char **argv)
{
	t_map *map;
	t_player *player;

	initialize_map_and_player(&map, &player);
	check_args(argc, argv, map);
	free_srcs(map);
	return (0);
}
