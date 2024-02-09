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
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	int		**c;
	int		**f;
	int			height;
}           t_map;

#endif

/*			MAP MANAGEMENT		*/
void	process_map(int fd, t_map *map, char **argv);
int		go_to_map(int fd);
void	check_map(int fd, t_map *map);
int		count_lines(char **file);
void	check_map_pos(t_map *map);
void	map_height(t_map *map, int i);
void	check_first_line(t_map *map);
void	check_body(t_map *map);
void	element_finder(t_map *map);
void	is_valid_rgb(char *str, t_map *map, char id);
void	rute_filler(t_map *map, char *rute, char *valid_rute);
/*			FREE SRCS			*/
void	free_srcs(t_map *map);
int		**ft_split_int(char *s, char c);
void	rgb_is_digit(char **strs);
