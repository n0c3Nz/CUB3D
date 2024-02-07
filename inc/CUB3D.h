#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>
# include "mlx/mlx.h"
# include "Libft/libft.h"
# include "./get_next_line/get_next_line.h"
# define BUFFER 1024
#define DEBUG_TRACE_ENTER printf("Entrando a la función %s\n", __func__);
#define DEBUG_TRACE_EXIT printf("Saliendo de la función %s\n", __func__);



typedef struct s_player
{
	int     x;
	int     y;
}           t_player;

typedef struct s_map
{
	t_player	*player;
	int			file_lines;
	int			**map;
	char		**file;
	int			width;
	int			height;
}           t_map;

#endif

/*			MAP MANAGEMENT		*/
void	process_map(int fd, t_map *map, char **argv);
int		go_to_map(int fd);
void	check_map(int fd, t_map *map);
void	check_first_line(t_map *map);
void	check_body(char *line);
void	check_map_pos(t_map *map);
int		count_lines(char **file);
void	map_height(t_map *map, int i);
/*			FREE SRCS			*/
void	free_srcs(t_map *map);