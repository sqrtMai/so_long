#include "so_long.h"

static void init_window(t_fdf *fdf)
{
	fdf->mlx = mlx_init();
	fdf->window = mlx_new_window(fdf->mlx, 1920, 1080, "so_long");
	fdf->img.img = mlx_new_image(fdf->mlx, 1920, 1080);
	fdf->img.addr = mlx_get_data_addr(fdf->img.img, &fdf->img.bits_per_pixel, &fdf->img.line_length,
									  &fdf->img.endian);
	fdf->img.width = 1920;
	fdf->img.height = 1080;
	mlx_hook(fdf->window, 2, 1L << 0, key_hook, fdf);
	mlx_hook(fdf->window, 17, 0, close_window, fdf);

	mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->img.img, 0, 0);
	mlx_loop(fdf->mlx);
}
static t_point **malloc_map(t_fdf *fdf)
{
	int i;
	t_point **points;

	i = 0;
	points = malloc(sizeof(t_point *) * fdf->map->map_height);
	if (!points)
		return NULL; //TODO free tout;
	while (i < fdf->map->map_height)
	{
		points[i] = malloc(sizeof(t_point) * (fdf->map->map_len));
		if (!points[i])
			return NULL; //TODO free tout;
		i++;
	}
	return points;
}

static void put_datas_to_point(t_fdf *fdf)
{
	int i;
	int y;
	char **split;

	i = 0;
	split = ft_split(fdf->map->map, "\n");
	if (!split)
		return (free_hub(fdf, 1));
	fdf->map->points = malloc_map(fdf);
	while (split[i])
	{
		y = 0;
		while (split[i][y] && split[i])
		{
			fdf->map->points[i][y].type = split[i][y];
			fdf->map->points[i][y].x = y;
			fdf->map->points[i][y++].y = i;
		}
		i++;
	}
	free_everything((void **)split);
	check_walls(fdf);
}

static void init_struct(t_fdf *fdf, char *map)
{
	fdf->map = malloc(sizeof(t_map));
	if (!fdf->map)
		exit(1);
	fdf->map->points = NULL;
	fdf->map->map = read_map(map, fdf);
	check_valid_size(fdf, fdf->map->map);
	fdf->map->map_height = get_map_height(fdf->map->map);
	fdf->map->map_len = get_map_len(fdf->map->map);
	if ((fdf->map->map_len < 3 || fdf->map->map_height < 3) ||
		(fdf->map->map_len == 3 && fdf->map->map_height < 6) ||
		(fdf->map->map_height == 3 && fdf->map->map_len < 6) )
		return (ft_printf("The map doesn't have a correct size"), free_hub(fdf, -1));
	if (check_valid_map(fdf->map->map) != 3)
		return (ft_printf("Map requirements not respected"),
				free_hub(fdf, -1));
}

void init_datas(t_fdf *fdf, char *map)
{
	init_struct(fdf, map);
	put_datas_to_point(fdf);
	init_window(fdf); //TODO Faire une fonction qui ajuste la tailel de la fenêtre selon la map
}
