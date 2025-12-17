#include "so_long.h"

int init_sprites(t_fdf *fdf)
{
	fdf->sprites->sprite1 = mlx_xpm_file_to_image(fdf->mlx,
	"textures/TILE.xpm", &fdf->sprites->sprites_size, &fdf->sprites->sprites_size);
	if (!fdf->sprites->sprite1)
		return ft_printf_error("Error\nTILE.xpm not found"), free_things(fdf, -1), 1;
	fdf->sprites->sprite2 = mlx_xpm_file_to_image(fdf->mlx, "textures/WALL.xpm",
		&fdf->sprites->sprites_size, &fdf->sprites->sprites_size);
	if (!fdf->sprites->sprite2)
		return ft_printf_error("Error\nWALL.xpm not found"), free_things(fdf, -1), 1;
	fdf->sprites->sprite3 = mlx_xpm_file_to_image(fdf->mlx, "textures/BABA.xpm",
		&fdf->sprites->sprites_size, &fdf->sprites->sprites_size);
	if (!fdf->sprites->sprite3)
		return ft_printf_error("Error\nBABA.xpm not found"), free_things(fdf, -1), 1;
	fdf->sprites->sprite4 = mlx_xpm_file_to_image(fdf->mlx, "textures/ORB.xpm",
		&fdf->sprites->sprites_size, &fdf->sprites->sprites_size);
	if (!fdf->sprites->sprite4)
		return ft_printf_error("Error\nORB.xpm not found"), free_things(fdf, -1), 1;
	fdf->sprites->sprite5 = mlx_xpm_file_to_image(fdf->mlx, "textures/FLAG.xpm",
		&fdf->sprites->sprites_size, &fdf->sprites->sprites_size);
	if (!fdf->sprites->sprite5)
		return ft_printf_error("Error\nFLAG.xpm not found"), free_things(fdf, -1), 1;
	return 0;
}

static void init_window(t_fdf *fdf)
{
	fdf->mlx = mlx_init();
	fdf->window = mlx_new_window(fdf->mlx, fdf->map->map_len * 75, fdf->map->map_height * 75, "so_long");
	fdf->img.width = 75;
	fdf->img.height = 75;
	mlx_hook(fdf->window, 3, 1L << 1, key_hook, fdf);
	mlx_hook(fdf->window, 17, 0, close_window, fdf);
	init_sprites(fdf);
	print_map(fdf);
	mlx_loop_hook(fdf->mlx, draw_player, fdf);
	mlx_loop(fdf->mlx);
}

static void init_to_null(t_fdf *fdf)
{
	fdf->map->points = NULL;
	fdf->mlx = NULL;
	fdf->window = NULL;
	fdf->sprites->sprites_size = 0;
	fdf->sprites->sprite1 = NULL;
	fdf->sprites->sprite2 = NULL;
	fdf->sprites->sprite3 = NULL;
	fdf->sprites->sprite4 = NULL;
	fdf->sprites->sprite5 = NULL;
	fdf->map->moves = 0;
}
static void init_struct(t_fdf *fdf, char *map)
{
	fdf->map = malloc(sizeof(t_map));
	if (!fdf->map)
		exit(1);
	fdf->map->collectibles = 0;
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
	init_to_null(fdf);
}

void init_datas(t_fdf *fdf, char *map)
{
	init_struct(fdf, map);
	put_datas_to_point(fdf);
	init_window(fdf); // TODO Faire une fonction qui ajuste la tailel de la fenêtre selon la map
}
