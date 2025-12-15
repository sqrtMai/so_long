#include "so_long.h"

void init_window(t_fdf *fdf)
{
	fdf->mlx = mlx_init();
	fdf->window = mlx_new_window(fdf->mlx, 1920, 1080, "FdF");
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
static void put_datas_to_point(t_fdf *fdf, char **split)
{
	int i;
	int y;

	i = 0;
	y = 0;
	fdf->map->points = malloc(sizeof(t_point *) * fdf->map->map_height);
	if (!fdf->map->points)
		return ; //TODO free tout;
	while (i < fdf->map->map_height)
	{
		fdf->map->points[i] = malloc(sizeof(t_point) * (fdf->map->map_len));
		if (!fdf->map->points[i++])
			return ; //TODO free tout;
	}
	i = 0;
	while (split[i])
	{
		y = 0;
		while (split[i][y] && split[i])
		{
			fdf->map->points[i][y].type = split[i][y];
			fdf->map->points[i][y].x = y;
			fdf->map->points[i][y].y = i;
			y++;
		}
		i++;
	}
	free_everything((void **)split);
}

int check_valid_map(char *map)
{
	int exit;
	int start;
	int collectible;
	int i;

	exit = 0;
	start = 0;
	collectible = 0;
	i = 0;
	while (map[i])
	{
		if (map[i] == 'E')
			exit = 1;
		if (map[i] == 'P')
			start = 1;
		if (map[i] == 'C')
			collectible = 1;
		if (map[i] != 'P' && map[i] != 'C' && map[i] != 'E' && map[i] != '1' && map[i] != '0' && map[i] != '\n')
			return 0;
		i++;
	}
	return (exit + start + collectible);
}

static void init_struct(t_fdf *fdf, char *map)
{
	fdf->map = malloc(sizeof(t_map));
	fdf->map->map = read_map(map);
	check_valid_size(fdf, fdf->map->map);
	fdf->map->map_height = get_map_height(fdf->map->map);
	fdf->map->map_len = get_map_len(fdf->map->map);
	if (fdf->map->map_height == fdf->map->map_len)
		return (ft_printf("pas la bonne size"), exit(1));
	if (check_valid_map(fdf->map->map) != 3)
		return (ft_printf("invalid map adfddddaa"), exit(1));
}

int check_walls(t_fdf *fdf)
{
	int i;
	int y;

	i = 0;
	while (i < fdf->map->map_height)
	{
		y = 0;
		while (y < fdf->map->map_len)
		{
			if (i == 0 && fdf->map->points[i][y].type != '1')
					return 0;
			if ((i > 0 && i < fdf->map->map_height - 1) &&
				fdf->map->points[i][0].type != '1' || fdf->map->points[i][fdf->map->map_len - 1].type != '1')
					return 0;
			if (i == fdf->map->map_height - 1 && fdf->map->points[i][y].type != '1')
					return 0;
			y++;
		}
		i++;
	}
	return 1;
}
void init_datas(t_fdf *fdf, char *map)
{
	char **split;

	init_struct(fdf, map);
	split = ft_split(fdf->map->map, "\n");
	put_datas_to_point(fdf, split);
	if (!check_walls(fdf))
		ft_printf("\nincorrect map aaa"); //TODO return et free
	else
		ft_printf("good");
	// init_window(fdf);
}
