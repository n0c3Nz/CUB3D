/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CUB3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guortun- <guortun-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 10:43:04 by guortun-          #+#    #+#             */
/*   Updated: 2024/05/15 10:43:05 by guortun-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>
# include <sys/time.h>

# include "mlx_linux/mlx.h"
# if (__linux__)
	# include "key_linux.h"
# else
	#include "key_macos.h"
# endif
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"

# define BUFFER 1024
# define DEBUG_TRACE_ENTER printf("Entrando a la función %s\n", __func__);
# define DEBUG_TRACE_EXIT printf("Saliendo de la función %s\n", __func__);

# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_RELEASE	3

# define width 1920
# define height 1080

typedef struct s_rnd
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
	int			Xtex;
	int			Ytex;
	long long	time;
	long long	oldtime;
	int			frametime;
	unsigned int	verLinecolor;
}				t_rnd;

typedef struct s_img
{
	void	*img;
	int		*addr;
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
	int		sy;
	int		sx;
	char	**lines;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		m_f;
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
	t_rnd		*rnd;
	t_img		sprites[4];
	t_img		img;
	t_cam		cam;
	t_player	player;
	t_map		map;
	t_key		key;
}	t_cub;

/*			INIT_FUNCS.c		*/
int		first_check(int argc, char **argv);
int		initialize_map_and_rnd(t_cub **cub, t_rnd **rnd);
int		digest_map(int argc, char **argv, t_cub **cub);
int		init_mlx(t_cub **cub);
void	set_orientation(t_player *player, double *planeX, double *planeY);
/*			PLAYER INTERACTION		*/
void	mouv_player_left(t_cub *cub);
void	mouv_player_right(t_cub *cub);
void	rotate_player_right(t_cub *cub);
void	rotate_player_left(t_cub *cub);
void	mouv_backwards(t_cub *cub);
/*			EXIT		*/
void    free_map(t_cub *cub);
int		ft_exit_free_img(t_cub *cub);
int		ft_exit_free_img_error(t_cub *cub);
int		ft_putstr_err(char *str);
void	error_msg(char *msg);
/*			FILE_CHECK.c		*/
int		check_file(int fd, t_cub **cub);
int		trim_and_fill(t_cub **cub, char *buffer, int *map_length, int *player_count);
void	get_texture(t_cub **cub, char *line);
void	analyse_file(t_cub **cub, char *line, int *player_count, int *map_length);
int		get_map(t_cub *cub, char *line, int *player_count, int *map_length);
int		check_texture_direction(t_cub **cub, char *line, int *player_count, int *map_length);
int		get_color(t_cub *cub, char *line);
/*			FILE_CHECK_3.c		*/
int		check_last_line(char *line, int j, int k, int file_lines);
void	check_alloc(t_cub *cub, int *i);
/*			FILE_UTILS.c		*/
int		check_map_data(t_cub **cub, char *buffer);
int		check_limit(char *line);
void	check_route(char *route);
int		rgb_to_hex(t_cub *cub, char *rgb);
int		process_line(int *map_length, char *line, int *i);
/*			FILE_UTILS_2.c		*/
void	update_player(t_cub *cub, int map_length, int i, char *line);
int		validate_and_free_rgb(char **rgb_split, char *rgb);
int		process_rgb(char **rgb_split, char *rgb, t_cub *cub);
/*			FILL_MAP_UTILS.c		*/
int		find_long_line(char *buffer);
char	**allocate_memory(int lines);
int		check_bff_and_fill_lines(char buffer_k, char *lines_ij, int *j);
/*			FILL_MAP.c		*/
int		fill_map(t_cub **cub, char *buffer);
/*			MLX_PROCESS.c		*/
int		main_loop(t_cub *cub);
long	timenow(struct timeval *te);
void	show_fps(t_cub *cub);
void	blscr_img(t_cub *cub);
/*			KEY_HOOK.C			*/
void	key_update(t_cub *cub);
int		key_press(int key, t_cub *info);
int		key_release(int key, t_cub *info);
/*			RAYCASTING DDA */
void	calc(t_cub *cub);
void	create_plans(t_cub *cub, int x);
void	raydir(t_cub *cub, int x);
void	raydir2(t_cub *cub, int x);
void	ray2wall(t_cub *cub);
void	which_side_ray_collide(t_cub *cub);
void	getraycoords(t_cub *cub);
/*			FLOOR */
void	drawfloor_ceiling(t_cub *cub, int x);
/*			SPRITES*/
void	ft_texture_loop(t_cub *cub, int x);
#endif
