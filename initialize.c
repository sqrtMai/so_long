#include "so_long.h"

void print_case(t_fdf *fdf, char c, int z, int l)
{
	if (c == '0')
	{
		mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->sprites->sprite1, z, l);
		z += 75;
	}
	else if (c == '1')
	{
		mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->sprites->sprite2, z, l);
		z += 75;
	}
	else if (c == 'P')
	{
		mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->sprites->sprite3, z, l);
		z += 75;
	}
	else if (c == 'C')
	{
		mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->sprites->sprite4, z, l);
		z += 75;
	}
	else if (c == 'E')
	{
		mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->sprites->sprite5, z, l);
		z += 75;
	}
}

void print_map(t_fdf *fdf)
{
	int y;
	int i;
	int z;
	int l;

	y = 0;
	i = 0;
	l = 0;
	while (i < fdf->map->map_height)
	{
		y = 0;
		z = 0;
		while (y < fdf->map->map_len)
		{
			print_case(fdf, fdf->map->points[i][y].type, z, l);
			z += 75;
			y++;
		}
		l += 75;
		i++;
	}
}

void init_sprites(t_fdf *fdf)
{
	fdf->sprites->sprite1 = mlx_xpm_file_to_image(fdf->mlx, "textures/TILE.xpm",
												  &fdf->sprites->sprites_size, &fdf->sprites->sprites_size);
	fdf->sprites->sprite2 = mlx_xpm_file_to_image(fdf->mlx, "textures/WALL.xpm",
												  &fdf->sprites->sprites_size, &fdf->sprites->sprites_size);
	fdf->sprites->sprite3 = mlx_xpm_file_to_image(fdf->mlx, "textures/BABA.xpm",
												  &fdf->sprites->sprites_size, &fdf->sprites->sprites_size);
	fdf->sprites->sprite4 = mlx_xpm_file_to_image(fdf->mlx, "textures/ORB.xpm",
												  &fdf->sprites->sprites_size, &fdf->sprites->sprites_size);
	fdf->sprites->sprite5 = mlx_xpm_file_to_image(fdf->mlx, "textures/FLAG.xpm",
												  &fdf->sprites->sprites_size, &fdf->sprites->sprites_size);
}

static void init_window(t_fdf *fdf)
{
	fdf->mlx = mlx_init();
	fdf->window = mlx_new_window(fdf->mlx, fdf->map->map_len * 75, fdf->map->map_height * 75, "so_long");
	fdf->img.width = 75;
	fdf->img.height = 75;
	mlx_hook(fdf->window, 2, 1L << 0, key_hook, fdf);
	mlx_hook(fdf->window, 17, 0, close_window, fdf);
	init_sprites(fdf);
	print_map(fdf);
	mlx_loop(fdf->mlx);
}
static t_point **malloc_map(t_fdf *fdf)
{
	int i;
	t_point **points;

	i = 0;
	points = malloc(sizeof(t_point *) * fdf->map->map_height);
	if (!points)
		return NULL; // TODO free tout;
	while (i < fdf->map->map_height)
	{
		points[i] = malloc(sizeof(t_point) * (fdf->map->map_len));
		if (!points[i])
			return NULL; // TODO free tout;
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
		return (free_things(fdf, 1));
	fdf->map->points = malloc_map(fdf);
	while (split[i])
	{
		y = 0;
		while (split[i][y] && split[i])
		{
			fdf->map->points[i][y].type = split[i][y];
			if (split[i][y] == 'C')
				fdf->map->collectibles++;
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
	fdf->map->collectibles = 0;
	;
	fdf->map->flood_fill = 0;
	fdf->map->map = read_map(map, fdf);
	check_valid_size(fdf, fdf->map->map);
	fdf->map->map_height = get_map_height(fdf->map->map);
	fdf->map->map_len = get_map_len(fdf->map->map);
	if ((fdf->map->map_len < 3 || fdf->map->map_height < 3) ||
		(fdf->map->map_len == 3 && fdf->map->map_height < 6) ||
		(fdf->map->map_height == 3 && fdf->map->map_len < 6))
		return (ft_printf("The map doesn't have a correct size"), free_things(fdf, -1));
	if (check_valid_map(fdf->map->map) != 3)
		return (ft_printf("Map requirements not respected"),
				free_things(fdf, -1));
	fdf->map->split_copy = ft_split(fdf->map->map, "\n");
	fdf->map->size.x = fdf->map->map_len;
	fdf->map->size.y = fdf->map->map_height;
	fdf->sprites = malloc(sizeof(t_sprite));
	fdf->sprites->sprites_size = 0;
}

void init_datas(t_fdf *fdf, char *map)
{
	init_struct(fdf, map);
	put_datas_to_point(fdf);
	init_window(fdf); // TODO Faire une fonction qui ajuste la tailel de la fenêtre selon la map
}
