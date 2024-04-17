#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>
# include <sys/time.h>
# include <mlx/mlx.h>
# include "key_macos.h"
# include "Libft/libft.h"
# include "get_next_line/get_next_line.h"

# define BUFFER 1024
# define DEBUG_TRACE_ENTER printf("Entrando a la función %s\n", __func__);
# define DEBUG_TRACE_EXIT printf("Saliendo de la función %s\n", __func__);

# define X_EVENT_KEY_PRESS		2
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
	int			wallX;
	int			lineHeight;
	int			drawStart;
	int			drawEnd;
	long long	time;
	long long	oldtime;
	int			frametime;
	int			verLinecolor;
}				t_render;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}				t_img;

typedef struct s_cam
{
	double	camera_angle_x;
	double	camera_angle_y;
	double	sensitivity;
}				t_cam;

typedef struct s_player
{
	double	posX;
	double	posY;
	double	moveSpeed;
	double	rotSpeed;
	char	dir;
	double 	dirX;
	double 	dirY;
}				t_player;

typedef struct s_map
{
	int		map_size;
	char	**lines;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		c;
	int		f;
}				t_map;

typedef struct s_key
{
	int	key_a;
	int key_w;
	int key_s;
	int key_d;
	int key_ar_l;
	int key_ar_r;
	int key_esc;
}			t_key;

typedef struct s_cub
{
	void		*mlx;
	void		*mlx_win;
	t_render	*render;
	t_img		*img;
	t_cam		cam;
	t_player	player;
	t_map		map;
	t_key		key;
}           t_cub;

/*			INIT_FUNCS.c		*/
void	check_args(int argc, char **argv, t_cub *cub);
void	initialize_map_and_render(t_cub **cub, t_render **render);//, t_player **player);
void	free_srcs(t_cub *cub);
/*			FILE_CHECK.c		*/
void	check_file(int fd, t_cub *cub);
void	trim_and_fill(t_cub *cub, char *buffer, int *map_length, int *player_count);
void	analyse_file(t_cub *cub, char *line, int *player_count, int *map_length);
/*			FILE_UTILS.c		*/
void	error_msg(char *msg, t_cub *cub);
void	check_limit(char *line);
void	check_route(char *route);
int		rgb_to_hex(t_cub *cub, char *rgb);
/*			FILL_MAP_UTILS.c		*/
int		find_long_line(char *buffer);
char	**allocate_memory(t_cub *cub, int lines);
int		checkBufferAndFillLines(char buffer_k, char *lines_ij, int *j);
/*			FILL_MAP.c		*/
void	fill_map(t_cub *cub, char *buffer);

/*			FILE_CHECK_2.c		*/
void	process_map(int fd, t_cub *cub, char **argv);
/*			MLX_PROCESS.c		*/
void	my_mlx_pixel_putcolor(t_img *img, int x, int y, int color);
int		main_loop(t_cub *cub);
void	calc(t_cub *cub);
/*			KEY_HOOK.C			*/
void	key_update(t_cub *cub);
int		key_press(int key, t_cub *info);
int		key_release(int key, t_cub *info);
/*			MINIMAP NAVIGATION */
// int		draw_minimap(t_cub *cub);
/*			RAYCASTING DDA */
void	create_plans(t_cub *cub, int x);
void	raydir(t_cub *cub, int x);
void	raydir2(t_cub *cub, int x);
void	ray2wall(t_cub *cub);
void	which_side_ray_collide(t_cub *cub);
void	getraycoords(t_cub *cub);
/*			FLOOR */
void	drawfloor_ceiling(t_cub *cub, int x);
int		mouse_handler(int x, int y, t_cub *cub);
long	long	timenow(struct timeval *te);
void	blscr_img(t_cub *cub);
int		adios(t_cub *cub);
#endif
