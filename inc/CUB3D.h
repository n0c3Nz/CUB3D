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
# define DEBUG_TRACE_ENTER printf("Entrando a la función %s\n", __func__);
# define DEBUG_TRACE_EXIT printf("Saliendo de la función %s\n", __func__);


typedef struct s_player
{
	int     x;
	int     y;
	char	dir;
	int		turn_dir;
	int		walk_dir;
	int		walk_speed;
	int		turn_speed;
	int		fov;
	int		fov_angle;
	int		fov_start;
	int		fov_end;
}           t_player;


typedef struct s_map
{
	t_player	*player;
	int			player_count;
	int			file_lines;
	char		**map;
	void		*mlx;
	void		*mlx_win;
	char		**file;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	int			**c;
	int			**f;
	int			height;
}           t_map;

/*			INIT_FUNCS.c		*/
void	check_args(int argc, char **argv, t_map *map);
void	initialize_map_and_player(t_map **map, t_player **player);
void	free_srcs(t_map *map);
/*			FILE_CHECK.c		*/
void	map_height(t_map *map, int i);
int		count_lines(char **file);
void	check_items(t_map *map);
void	check_map(int fd, t_map *map);
int		**ft_split_int(char *s, char c);
/*			FILE_CHECK_2.c		*/
void	process_map(int fd, t_map *map, char **argv);
int		go_to_map(int fd);
void	check_map_pos(t_map *map);
void	element_finder(t_map *map);
/*			FILE_CHECK_3.c		*/
void	dump_map(t_map *map);
void	rute_filler(t_map *map, char *rute, char *valid_rute);
void	is_valid_rgb(char *str, t_map *map, char id);
void	rgb_is_digit(char **strs);
/*			MAP_CHECK.c			*/
void	check_first_line(t_map *map);
void	check_body(t_map *map);
void	check_last_line(t_map *map);
/*			MLX_PROCESS.c		*/
void	mlx_run(t_map *map);

#endif
