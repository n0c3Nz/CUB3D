#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>
# include "mlx/mlx.h"
# include "key_macos.h"
# include "Libft/libft.h"
# include "get_next_line/get_next_line.h"

# define BUFFER 1024
# define DEBUG_TRACE_ENTER printf("Entrando a la función %s\n", __func__);
# define DEBUG_TRACE_EXIT printf("Saliendo de la función %s\n", __func__);

#define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_RELEASE	3

# define width 640
# define height 480

# define mapWidth 24
# define mapHeight 24

typedef struct s_render
{
	double 		planeX;
	double 		planeY;
	double		cameraX;
	double		rayDirX;
	double		rayDirY;
	int			mapX;
	int			mapY;
	double		sideDistX;
	double		sideDistY;
	double		deltaDistX;
	double		deltaDistY;
	double		perpWallDist;
	int			stepX;
	int			stepY;
	int			hit;
	int			side;
	int			lineHeight;
	int			drawStart;
	int			drawEnd;
	int			verLinecolor;

}		t_render;

typedef struct s_map
{
	t_render	*render;
	int			player_count;
	int			file_lines;
	int			map_size;
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
	double 		posX;
	double 		posY;
	char		dir;
	double 		dirX;
	double 		dirY;
	int			map_height;
	int			key_a;
	int			key_w;
	int			key_s;
	int			key_d;
	int			key_esc;
	double		moveSpeed;
	double		rotSpeed;
	int			texWidth;
	int			texHeight;
}           t_map;
/*			INIT_FUNCS.c		*/
void	check_args(int argc, char **argv, t_map *map);
void	initialize_map_and_render(t_map **map, t_render **render);//, t_player **player);
void	ft_free_array(char **array, int size);
void	ft_free_array_int(int **array, int size);
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
int		main_loop(t_map *map);
void	calc(t_map *map);
/*			KEY_HOOK.C			*/
void	key_update(t_map *map);
int		key_press(int key, t_map *info);
int		key_release(int key, t_map *info);

#endif
