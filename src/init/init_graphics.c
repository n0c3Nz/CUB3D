#include "../../inc/CUB3D.h"
int	first_check(int argc, char **argv)
{
	int	fd;
	if (argc != 2)
		return (ft_putstr_err("Error: Invalid number of arguments\n"));
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4))
		return (ft_putstr_err("Error: Invalid file extension\n"));
	fd = open(argv[1], O_RDONLY);
	if (fd <= 0)
		return (ft_putstr_err("Error: Invalid file route\n"));
	close(fd);
	return (0);
}
static	int	create_image_from_xpm(t_cub *cub, int img_num, char *texpath)
{
	int	x_size_tex;
	int	y_size_tex;
	x_size_tex = 64;
	y_size_tex = 64;
	cub->sprites[img_num].img = mlx_xpm_file_to_image(cub->mlx,
			texpath, &x_size_tex, &y_size_tex);
	if (cub->sprites[img_num].img == NULL)
		return (ft_putstr_err("Error: cannot create img from xpm\n"));
	cub->sprites[img_num].addr = (int *)mlx_get_data_addr(
			cub->sprites[img_num].img,
			&cub->sprites[img_num].bpp,
			&cub->sprites[img_num].line_len,
			&cub->sprites[img_num].endian);
	return (0);
}
int	init_textures(t_cub *cub)
{
	int	err;
	err = 0;
	err = create_image_from_xpm(cub, 0, cub->map.no);
	err = create_image_from_xpm(cub, 1, cub->map.so);
	err = create_image_from_xpm(cub, 2, cub->map.ea);
	err = create_image_from_xpm(cub, 3, cub->map.we);
	return (err);
}
int	init_mlx(t_cub **cub)
{
	(*cub)->mlx = mlx_init();
	if ((*cub)->mlx == NULL)
		return (ft_putstr_err("Error: MLX unable to init\n      X_X\n"));
	(*cub)->mlx_win = mlx_new_window((*cub)->mlx, width, height, "CUB3D");
	if ((*cub)->mlx_win == NULL)
		return (ft_putstr_err("Error: MLX window unable to init\n      X_X\n"));
	(*cub)->img.img = mlx_new_image((*cub)->mlx, width, height);
	if (!(*cub)->img.img)
	{
		free((*cub)->img.img);
		mlx_destroy_window((*cub)->mlx, (*cub)->mlx_win);
		return (ft_putstr_err("Error: malloc t_img *\n      X_X\n"));
	}
	(*cub)->img.addr = (int *)mlx_get_data_addr(
			(*cub)->img.img,
			&(*cub)->img.bpp,
			&(*cub)->img.line_len,
			&(*cub)->img.endian);
	if (init_textures(*cub))
		return (1);
	return (0);
}