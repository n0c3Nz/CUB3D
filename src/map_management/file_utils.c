#include "CUB3D.h"
int	check_map_data(t_cub **cub, char *buffer)
{
	if ((*cub)->map.no == NULL || (*cub)->map.so == NULL
		|| (*cub)->map.we == NULL || (*cub)->map.ea == NULL)
		return (ft_putstr_err("Error: Missing texture\n"));
	if ((*cub)->map.f == 0 || (*cub)->map.c == 0)
		return (ft_putstr_err("Error: Missing color\n"));
	if (fill_map(cub, buffer))
		return (1);
	return (0);
}
int	check_limit(char *line)
{
	int	i;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != '1' && line[i] != ' ' && line[i] != '\n')
			return (ft_putstr_err("Error: Map is not closed\n"));
		i++;
	}
	return (0);
}
void	check_route(char *route)
{
	int	fd;
	if (*route == '\0')
		error_msg("Error: Invalid texture route");
	if (ft_strncmp(route + ft_strlen(route) - 4, ".xpm", 4))
		error_msg("Error: Invalid texture extension");
	fd = open(route, O_RDONLY);
	if (fd <= 0)
		error_msg("Error: Invalid texture route");
	close(fd);
}
int	rgb_to_hex(t_cub *cub, char *rgb)
{
	char	**rgb_split;
	int		hex;
	int		i;
	i = 0;
	if (ft_strlen(rgb) < 5)
		exit (0);
	while (rgb[i] != '\0')
	{
		if ((rgb[i] < 48 || rgb[i] > 57) && rgb[i] != ',')
			error_msg("Error: Invalid RGB format");
		i++;
	}
	i = 0;
	rgb_split = ft_split(rgb, ',');
	if (rgb_split == NULL || rgb_split[0] == NULL
		|| rgb_split[1] == NULL || rgb_split[2] == NULL)
	{
		free(rgb_split[2]);
		free(rgb_split[1]);
		free(rgb_split[0]);
		free(rgb_split);
		return (0);
	}
	return (process_rgb(rgb_split, rgb, cub));
}
int	process_line(int *map_length, char *line, int *i)
{
	if (ft_strlen(line) == 0)
		return (0);
	if (*map_length == 0)
	{
		if (check_limit(line))
			return (1);
		(*map_length)++;
		return (0);
	}
	while (line[*i] == '0')
		(*i)++;
	if (ft_strlen(line) < 3)
		return (ft_putstr_err("Error: Line of map is too short\n"));
	if ((line[*i] != '1' && line[*i] != ' ')
		|| (line[ft_strlen(line) - 1] != '1'
			&& line[ft_strlen(line) - 1] != ' '))
		return (ft_putstr_err("Error: Map is not closed\n"));
	return (0);
}